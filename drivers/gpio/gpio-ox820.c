/*
 * OX820 chip GPIO driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/* Supports:
 * OX820
 */

#include <linux/module.h>
#include <linux/pci.h>
#include <linux/platform_device.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/stddef.h>
#include <linux/interrupt.h>
#include <linux/init.h>
#include <linux/irq.h>
#include <linux/io.h>
#include <linux/spinlock.h>
#include <linux/gpio.h>
#include <linux/slab.h>
#include <linux/pm_runtime.h>
#include <mach/hardware.h>
#include <mach/irqs.h>
#include <asm/hw_irq.h>
#include <mach/mfctrl.h>
#include <mach/hw/gpio.h>

static DEFINE_SPINLOCK(oxnas_gpio_spinlock);

#if 0
#define ox820_printk(x...) printk(x)
#else
#define ox820_printk(x...) {}
#endif

#ifdef CONFIG_GPIO_OX820_USE_IRQ
int ox820_gpioa_irq_base = OX820_GPIO_IRQ_START;
int ox820_gpiob_irq_base = OX820_GPIO_IRQ_START + 32;

static irqreturn_t ox820_gpioa_irq_handler(int irq, void* dev_id)
{
	unsigned irqidx;
    struct ox820_gpio_registers_t* gpio = (struct ox820_gpio_registers_t*) GPIO_A_BASE;
	unsigned long irq_event = gpio->irq_event;
    gpio->irq_event = irq_event;
    wmb();
    chained_irq_enter(chip, desc);
    irqidx = find_first_bit(&irq_event, BITS_PER_LONG);
    while(irqidx < BITS_PER_LONG) {
		if(irq_event & (1UL << irqidx)) {
			generic_handle_irq(ox820_gpioa_irq_base + irqidx);
		}
        irqidx = find_next_bit(&irq_event, BITS_PER_LONG, irqidx + 1);
	}
    chained_irq_exit(chip, desc);
	
	return IRQ_HANDLED;
}

static void ox820_gpioa_irq_mask(struct irq_data* d)
{
	unsigned long flags;
	int irqno = d->irq - ox820_gpioa_irq_base;
    struct ox820_gpio_registers_t* gpio = (struct ox820_gpio_registers_t*) GPIO_A_BASE;
    
	spin_lock_irqsave(&oxnas_gpio_spinlock, flags);
	
    gpio->irq_enable_mask &= (~(1UL << irqno));
    gpio->irq_event = 1UL << (irqno);
    wmb();
	
	spin_unlock_irqrestore(&oxnas_gpio_spinlock, flags);
}

static void ox820_gpioa_irq_unmask(struct irq_data* d)
{
	unsigned long flags;
	int irqno = d->irq - ox820_gpioa_irq_base;
    struct ox820_gpio_registers_t* gpio = (struct ox820_gpio_registers_t*) GPIO_A_BASE;
	spin_lock_irqsave(&oxnas_gpio_spinlock, flags);
	
    gpio->irq_enable_mask |= (1UL << irqno);
	wmb();
	
	spin_unlock_irqrestore(&oxnas_gpio_spinlock, flags);
}

static int ox820_gpioa_irq_set_type(struct irq_data* d, unsigned int type)
{
	unsigned long flags;
    struct ox820_gpio_registers_t* gpio = (struct ox820_gpio_registers_t*) GPIO_A_BASE;
	int irqno = d->irq - ox820_gpioa_irq_base;
	if((type & IRQ_TYPE_EDGE_BOTH) && (type & IRQ_TYPE_LEVEL_MASK)) {
		printk("ox820_gpio: gpioa irq %d: unsupported type %d\n",
				d->irq, type);
		return -EINVAL;
	}

	spin_lock_irqsave(&oxnas_gpio_spinlock, flags);
	
	if((IRQ_TYPE_EDGE_RISING & type) || (IRQ_TYPE_LEVEL_HIGH & type)) {
        gpio->rising_edge_act_high_irq_enable |= (1UL << irqno);
	} else {
        gpio->rising_edge_act_high_irq_enable &= (~(1UL << irqno));
	}
	
	if((IRQ_TYPE_EDGE_FALLING & type) || (IRQ_TYPE_LEVEL_LOW & type)) {
        gpio->falling_edge_act_low_irq_enable |= (1UL << irqno);
	} else {
        gpio->falling_edge_act_low_irq_enable &= (~(1UL << irqno));
	}
	
	if(IRQ_TYPE_LEVEL_MASK & type) {
        gpio->level_interrupt_enable |= (1UL << irqno);
	} else {
        gpio->level_interrupt_enable &= (~(1UL << irqno));
	}
    wmb();
		
	spin_unlock_irqrestore(&oxnas_gpio_spinlock, flags);
	
	return 0;
}

static struct irq_chip gpio_a_irq_chip = {
	.name = "gpioa_irq",
	.irq_mask = ox820_gpioa_irq_mask,
	.irq_unmask = ox820_gpioa_irq_unmask,
	.irq_set_type = ox820_gpioa_irq_set_type
};

static irqreturn_t ox820_gpiob_irq_handler(int irq, void* dev_id)
{
	unsigned irqidx;
    struct ox820_gpio_registers_t* gpio = (struct ox820_gpio_registers_t*) GPIO_B_BASE;
	unsigned long irq_event = gpio->irq_event;
	gpio->irq_event = irq_event;
    wmb();
    chained_irq_enter(chip, desc);
    irqidx = find_first_bit(&irq_event, BITS_PER_LONG);
    while(irqidx < BITS_PER_LONG) {
		if(irq_event & (1UL << irqidx)) {
			generic_handle_irq(ox820_gpiob_irq_base + irqidx);
		}
        irqidx = find_next_bit(&irq_event, BITS_PER_LONG, irqidx + 1);
	}
    chained_irq_exit(chip, desc);
	
	return IRQ_HANDLED;
}

static void ox820_gpiob_irq_mask(struct irq_data* d)
{
	unsigned long flags;
    struct ox820_gpio_registers_t* gpio = (struct ox820_gpio_registers_t*) GPIO_B_BASE;
	int irqno = d->irq - ox820_gpiob_irq_base;
	spin_lock_irqsave(&oxnas_gpio_spinlock, flags);
	
    gpio->irq_enable_mask &= (~(1UL << irqno));
    gpio->irq_event = 1UL << irqno;
	wmb();
	
	spin_unlock_irqrestore(&oxnas_gpio_spinlock, flags);
}

static void ox820_gpiob_irq_unmask(struct irq_data* d)
{
	unsigned long flags;
    struct ox820_gpio_registers_t* gpio = (struct ox820_gpio_registers_t*) GPIO_B_BASE;
	int irqno = d->irq - ox820_gpiob_irq_base;
	spin_lock_irqsave(&oxnas_gpio_spinlock, flags);
	
    gpio->irq_enable_mask |= (1UL << irqno);
    wmb();
	
	spin_unlock_irqrestore(&oxnas_gpio_spinlock, flags);
}

static int ox820_gpiob_irq_set_type(struct irq_data* d, unsigned int type)
{
	unsigned long flags;
	int irqno = d->irq - ox820_gpiob_irq_base;
    struct ox820_gpio_registers_t* gpio = (struct ox820_gpio_registers_t*) GPIO_B_BASE;
	if((type & IRQ_TYPE_EDGE_BOTH) && (type & IRQ_TYPE_LEVEL_MASK)) {
		printk("ox820_gpio: gpiob irq %d: unsupported type %d\n",
				d->irq, type);
		return -EINVAL;
	}

	spin_lock_irqsave(&oxnas_gpio_spinlock, flags);
	
	if((IRQ_TYPE_EDGE_RISING & type) || (IRQ_TYPE_LEVEL_HIGH & type)) {
        gpio->rising_edge_act_high_irq_enable |= (1UL << irqno);
	} else {
        gpio->rising_edge_act_high_irq_enable &= (~(1UL << irqno));
	}
	
	if((IRQ_TYPE_EDGE_FALLING & type) || (IRQ_TYPE_LEVEL_LOW & type)) {
        gpio->falling_edge_act_low_irq_enable |= (1UL << irqno);
	} else {
        gpio->falling_edge_act_low_irq_enable &= (~(1UL << irqno));
	}
	
	if(IRQ_TYPE_LEVEL_MASK & type) {
        gpio->level_interrupt_enable |= (1UL << irqno);
	} else {
        gpio->level_interrupt_enable &= (~(1UL << irqno));
	}
    wmb();
		
	spin_unlock_irqrestore(&oxnas_gpio_spinlock, flags);
	
	return 0;
}

static struct irq_chip gpio_b_irq_chip = {
	.name = "gpiob_irq",
	.irq_mask = ox820_gpiob_irq_mask,
	.irq_unmask = ox820_gpiob_irq_unmask,
	.irq_set_type = ox820_gpiob_irq_set_type
};
#endif

static int ox820_gpio_direction_input(struct gpio_chip* chip, unsigned nr)
{
    struct ox820_gpio_registers_t* gpio;
	if(nr >= 50) {
		return -EINVAL;
	}
    
    if(nr >= 32) {
        gpio = (struct ox820_gpio_registers_t*) GPIO_B_BASE;
    } else {
        gpio = (struct ox820_gpio_registers_t*) GPIO_A_BASE;
    }
	
	ox820_printk(KERN_INFO"ox820_gpio.c: switch to input %u\n", nr);
	ox820_mf_select_gpio(nr);

    gpio->output_enable_clear = 1 << (nr & 31);
    wmb();
	
	return 0;
}

static int ox820_gpio_get(struct gpio_chip* chip, unsigned nr)
{
    struct ox820_gpio_registers_t* gpio;
	if(nr >= 50) {
		return 0;
	}
	
    if(nr >= 32) {
        gpio = (struct ox820_gpio_registers_t*) GPIO_B_BASE;
    } else {
        gpio = (struct ox820_gpio_registers_t*) GPIO_A_BASE;
    }
	
	ox820_printk(KERN_INFO"ox820_gpio.c: read input %u\n", nr);
    
    return !!(gpio->input & (1 << (nr & 31)));
}

static int ox820_gpio_set_debounce(struct gpio_chip* chip,
					unsigned nr,
					unsigned debounce)
{
	unsigned long flags;
    struct ox820_gpio_registers_t* gpio;
	if(nr >= 50) {
		return -EINVAL;
	}

    if(nr >= 32) {
        gpio = (struct ox820_gpio_registers_t*) GPIO_B_BASE;
    } else {
        gpio = (struct ox820_gpio_registers_t*) GPIO_A_BASE;
    }
	
	ox820_printk(KERN_INFO"ox820_gpio.c: set debounce mode for %u = %u\n", nr, debounce);
	ox820_mf_select_gpio(nr);
	
	spin_lock_irqsave(&oxnas_gpio_spinlock, flags);
    if(debounce) {
        gpio->debounce_enable |= (1 << (nr & 31));
    } else {
        gpio->debounce_enable &= (~(1 << (nr & 31)));
    }
    wmb();
	spin_unlock_irqrestore(&oxnas_gpio_spinlock, flags);
	
	return 0;
}

static int ox820_gpio_direction_output(struct gpio_chip* chip,
					unsigned nr,
					int val)
{
    struct ox820_gpio_registers_t* gpio;

	if(nr >= 50) {
		return -EINVAL;
	}
	
	ox820_printk(KERN_INFO"ox820_gpio.c: switch to output %u\n", nr);
	ox820_mf_select_gpio(nr);
	
    if(nr >= 32) {
        gpio = (struct ox820_gpio_registers_t*) GPIO_B_BASE;
    } else {
        gpio = (struct ox820_gpio_registers_t*) GPIO_A_BASE;
    }
    
    gpio->output_enable_set = 1 << (nr & 31);
	if(val) {
        gpio->output_set = 1 << (nr & 31);
	} else {
        gpio->output_clear = 1 << (nr & 31);
	}
    wmb();
	
	return 0;
}

static void ox820_gpio_set(struct gpio_chip* chip,
				unsigned nr,
				int val)
{
    struct ox820_gpio_registers_t* gpio;
	if(nr >= 50) {
		return;
	}

    if(nr >= 32) {
        gpio = (struct ox820_gpio_registers_t*) GPIO_B_BASE;
    } else {
        gpio = (struct ox820_gpio_registers_t*) GPIO_A_BASE;
    }
    
	ox820_printk(KERN_INFO"ox820_gpio.c: set output %u to %u\n", nr, val);
	if(val) {
        gpio->output_set = 1 << (nr & 31);
	} else {
        gpio->output_clear = 1 << (nr & 31);
	}
}

#ifdef CONFIG_GPIO_OX820_USE_IRQ
static int ox820_gpio_to_irq(struct gpio_chip* gpio, unsigned nr) {
	if(nr >= 50) {
		return -EINVAL;
	}
	if(nr < SYS_CTRL_NUM_PINS) {
		return ox820_gpioa_irq_base + nr;
	} else {
		return ox820_gpiob_irq_base + nr - SYS_CTRL_NUM_PINS;
	}
}
#endif

static struct gpio_chip ox820_gpio = {
	.label = "ox820_gpio",
	.dev = NULL,
	.owner = NULL,
	.direction_input = ox820_gpio_direction_input,
	.get = ox820_gpio_get,
	.direction_output = ox820_gpio_direction_output,
	.set_debounce = ox820_gpio_set_debounce,
	.set = ox820_gpio_set,
#ifdef CONFIG_GPIO_OX820_USE_IRQ
	.to_irq = ox820_gpio_to_irq,
#endif
	.base = 0,
	.ngpio = 50,
};

static int __devinit ox820_gpio_probe(struct platform_device* pdev)
{
	int ret = 0;
	
	return ret;
}

static int __devexit ox820_gpio_remove(struct platform_device* pdev)
{
	int ret = 0;
	return ret;
}

static struct platform_driver ox820_gpio_driver = {
	.driver = {
		.name = "ox820-gpio",
	},
	.probe = ox820_gpio_probe,
	.remove = ox820_gpio_remove
};

static int __init ox820_gpio_platform_init(void)
{
	int ret;
    struct ox820_gpio_registers_t* gpioa = (struct ox820_gpio_registers_t*) GPIO_A_BASE;
    struct ox820_gpio_registers_t* gpiob = (struct ox820_gpio_registers_t*) GPIO_B_BASE;
    
#ifdef CONFIG_GPIO_OX820_USE_IRQ
	int j;
#endif

	ret = platform_driver_register(&ox820_gpio_driver);
	if(0 != ret) {
		goto clean0;
	}
	/* disable interrupts for now */
    gpioa->irq_enable_mask = 0;
    gpiob->irq_enable_mask = 0;
    wmb();
	
#ifdef CONFIG_GPIO_OX820_USE_IRQ
	ret = request_irq(GPIOA_INTERRUPT, ox820_gpioa_irq_handler, IRQF_SHARED, "ox820-gpioa", &gpio_a_irq_chip);
	if(0 != ret) {
		goto clean1;
	}
	ret = request_irq(GPIOB_INTERRUPT, ox820_gpiob_irq_handler, IRQF_SHARED, "ox820-gpiob", &gpio_b_irq_chip);
	if(0 != ret) {
		goto clean2;
	}
#endif
	ret = gpiochip_add(&ox820_gpio);
	if(0 != ret) {
		goto clean3;
	}
#ifdef CONFIG_GPIO_OX820_USE_IRQ
	for(j = ox820_gpioa_irq_base; j < ox820_gpioa_irq_base + 32; ++j) {
		irq_set_chip(j, &gpio_a_irq_chip);
		irq_set_handler(j, handle_simple_irq);
		irq_modify_status(j, IRQ_NOREQUEST, 0);
	}
	for(j = ox820_gpiob_irq_base; j < ox820_gpiob_irq_base + 18; ++j) {
		irq_set_chip(j, &gpio_b_irq_chip);
		irq_set_handler(j, handle_simple_irq);
		irq_modify_status(j, IRQ_NOREQUEST, 0);
	}
#endif			
	printk(KERN_INFO"ox820_gpio: initialized\n");
	
	return 0;
	
clean3:
#ifdef CONFIG_GPIO_OX820_USE_IRQ
	free_irq(GPIOB_INTERRUPT, &gpio_b_irq_chip);
clean2:
	free_irq(GPIOA_INTERRUPT, &gpio_a_irq_chip);
clean1:
#endif
	platform_driver_unregister(&ox820_gpio_driver);
clean0:
	printk(KERN_ERR"ox820_gpio: initialization result %u\n", ret);
	return ret;
}

static void __exit ox820_gpio_platform_exit(void)
{	
#ifdef CONFIG_GPIO_OX820_USE_IRQ
	int j;
#endif
    struct ox820_gpio_registers_t* gpioa = (struct ox820_gpio_registers_t*) GPIO_A_BASE;
    struct ox820_gpio_registers_t* gpiob = (struct ox820_gpio_registers_t*) GPIO_B_BASE;
	
	/* disable interrupts */
    gpioa->irq_enable_mask = 0;
    gpiob->irq_enable_mask = 0;
    wmb();

#ifdef CONFIG_GPIO_OX820_USE_IRQ
	free_irq(GPIOB_INTERRUPT, &gpio_b_irq_chip);
	free_irq(GPIOA_INTERRUPT, &gpio_a_irq_chip);
	
	for(j = ox820_gpioa_irq_base; j < ox820_gpioa_irq_base + 32; ++j) {
		irq_modify_status(j, 0, IRQ_NOREQUEST);
		irq_set_chip(j, NULL);
	}
	for(j = ox820_gpiob_irq_base; j < ox820_gpiob_irq_base + 32; ++j) {
		irq_modify_status(j, 0, IRQ_NOREQUEST);
		irq_set_chip(j, NULL);
	}
#endif
	
	gpiochip_remove(&ox820_gpio);
	platform_driver_unregister(&ox820_gpio_driver);
}

MODULE_DESCRIPTION("OX820 GPIO driver");
MODULE_AUTHOR("Sven Bormann");
MODULE_LICENSE("GPL");

module_init(ox820_gpio_platform_init);
module_exit(ox820_gpio_platform_exit);
