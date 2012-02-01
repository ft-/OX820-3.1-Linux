/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/completion.h>
#include <linux/io.h>
#include <asm/sizes.h>
#include <asm/setup.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <mach/hardware.h>
#include <mach/irqs.h>
#include <mach/hw/rpsa.h>

/**************************************
 * SATA
 */
static struct resource sata_resources[] = {
    [0] = {
        .name       = "sata_registers",
        .start      = SATA_REG_BASE_PA,
        .end        = SATA_REG_BASE_PA + 0xFFFFF,
        .flags      = IORESOURCE_MEM
    },
    [1] = {
        .name       = "sata_irq",
        .start      = OX820_ARM_GIC_IRQ_SATA,
        .end        = OX820_ARM_GIC_IRQ_SATA,
        .flags      = IORESOURCE_IRQ
    }
};

static struct platform_device sata_device = {
    .name = "ox820-sata",
    .id = 0,
    .num_resources = ARRAY_SIZE(sata_resources),
    .resource = sata_resources,
    .dev.coherent_dma_mask = 0xFFFFFFFF,
};

/**************************************
 * GPIO
 */
#ifdef CONFIG_GPIO_OX820
static struct resource gpio_resources[] = {
    [0] = {
        .start      = GPIO_A_BASE_PA,
        .end        = GPIO_A_BASE_PA + sizeof(ox820_gpio_registers_t) - 1,
        .flags      = IORESOURCE_MEM
    },
    [1] = {
        .start      = GPIO_B_BASE_PA,
        .end        = GPIO_B_BASE_PA + sizeof(ox820_gpio_registers_t) - 1,
        .flags      = IORESOURCE_MEM
    },
    [2] = {
        .start      = OX820_ARM_GIC_IRQ_GPIO_A,
        .end        = OX820_ARM_GIC_IRQ_GPIO_B,
        .flags      = IORESOURCE_IRQ
    },
};

static struct platform_device gpio_device = {
    .name       = "ox820-gpio",
    .id         = 0,
    .num_resources = ARRAY_SIZE(gpio_resources),
    .resource = gpio_resources,
};
#endif

/**************************************
 * USB HOST
 */
static struct resource usb_resources[] = {
    [0] = {
        .start      = USBHOST_BASE_PA + 0x100,
        .end        = USBHOST_BASE_PA + 0x10100 - 1,
        .flags      = IORESOURCE_MEM,
    },
    [1] = {
        .start      = OX820_ARM_GIC_IRQ_USBHOST,
        .end        = OX820_ARM_GIC_IRQ_USBHOST,
        .flags      = IORESOURCE_IRQ,
    },
};

static u64 usb_dmamask = ~(u32)0;

static struct platform_device usb_host = {
    .name       = "oxnas-ehci",
    .id     = 0,
    .dev = {
        .dma_mask       = &usb_dmamask,
        .coherent_dma_mask  = 0xffffffff,
    },
    .num_resources  = ARRAY_SIZE(usb_resources),
    .resource   = usb_resources,
};

/**************************************
 * GMAC-A
 */
static struct resource gmaca_resources[] = {
    [0] = {
           .name       	= "gmaca-registers",
           .start      	= ETHA_BASE_PA,
           .end        	= ETHA_BASE_PA + 0xFFFFF,
           .flags      	= IORESOURCE_MEM
    },
    [1] = {
        .name       = "sata_irq",
        .start      = OX820_ARM_GIC_IRQ_GMAC_A,
        .end        = OX820_ARM_GIC_IRQ_GMAC_A,
        .flags      = IORESOURCE_IRQ
    }
};

static struct platform_device gmaca_device = {
    .name = "ox820-gmac",
    .id = 0,
    .num_resources = ARRAY_SIZE(gmaca_resources),
    .resource = gmaca_resources,
    .dev.coherent_dma_mask = 0xFFFFFFFF,
};

/**************************************
 * GMAC-B
 */
static struct resource gmacb_resources[] = {
    [0] = {
           .name       	= "gmacb-registers",
           .start      	= ETHB_BASE_PA,
           .end        	= ETHB_BASE_PA + 0xFFFFF,
           .flags      	= IORESOURCE_MEM
    },
    [1] = {
        .name       = "sata_irq",
        .start      = OX820_ARM_GIC_IRQ_GMAC_B,
        .end        = OX820_ARM_GIC_IRQ_GMAC_B,
        .flags      = IORESOURCE_IRQ
    }
};

static struct platform_device gmacb_device = {
    .name = "ox820-gmac",
    .id = 1,
    .num_resources = ARRAY_SIZE(gmacb_resources),
    .resource = gmacb_resources,
    .dev.coherent_dma_mask = 0xFFFFFFFF,
};

/**************************************
 * List of platform devices
 */
static struct platform_device *platform_devices[] __initdata = {
 	 &usb_host,
#ifdef CONFIG_GPIO_OX820
 	 &gpio_device,
#endif
 	 &gmaca_device,
 	 &sata_device,
};

static struct platform_device *nas7825_platform_devices[] __initdata = {
 	 &gmacb_device
};

static int __init ox820_init_devices(void)
{
	// Add common platform devices
	int ret;

	ret = platform_add_devices(platform_devices, ARRAY_SIZE(platform_devices));

	if(0 == ret) {
		struct ox820_rpsa_registers_t* const rpsa = (struct ox820_rpsa_registers_t*) RPSA_BASE;

		if(OX820_NAS7825 == rpsa->chip_id) {
			ret = platform_add_devices(nas7825_platform_devices, ARRAY_SIZE(nas7825_platform_devices));
		}
	}
	return ret;
}

arch_initcall(ox820_init_devices);

