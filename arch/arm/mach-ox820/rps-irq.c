/*
 * arch/arm/mach-ox820/rps-irq.c
 *
 * Copyright (C) 2009 Oxford Semiconductor Ltd
 *
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
#include <linux/init.h>
#include <linux/list.h>
#include <asm/irq.h>
#include <asm/mach/irq.h>
#include <mach/hardware.h>
#include <mach/rps-irq.h>
#include <mach/hw/rpsa.h>

/* change the system interrupt number into an RPS interrupt number */
static inline unsigned int ox820_rps_irq_to_bitno(struct irq_data *d) {
	return d->irq - OX820_RPSA_IRQ_START;
}

static void ox820_rps_ack_irq(struct irq_data *d)
{
    struct ox820_rpsa_registers_t* const rpsa = (struct ox820_rpsa_registers_t*) RPSA_BASE;
    rpsa->irq_disable_control = (1UL << ox820_rps_irq_to_bitno(d));
}

static void ox820_rps_mask_irq(struct irq_data *d)
{
    struct ox820_rpsa_registers_t* const rpsa = (struct ox820_rpsa_registers_t*) RPSA_BASE;
    rpsa->irq_disable_control = (1UL << ox820_rps_irq_to_bitno(d));
}

static void ox820_rps_unmask_irq(struct irq_data *d)
{
    struct ox820_rpsa_registers_t* const rpsa = (struct ox820_rpsa_registers_t*) RPSA_BASE;
    rpsa->irq_enable_control = (1UL << ox820_rps_irq_to_bitno(d));
}

static struct irq_chip ox820_rps_chip = {
	.name		= "ox820-rps",
	.irq_ack	= ox820_rps_ack_irq,
	.irq_mask	= ox820_rps_mask_irq,
	.irq_unmask 	= ox820_rps_unmask_irq,
};

static void ox820_rps_irq(unsigned int irq, struct irq_desc *desc) {
	struct ox820_rpsa_registers_t* const rpsa = (struct ox820_rpsa_registers_t*) RPSA_BASE;
	struct irq_chip *chip = irq_get_chip(irq);
	int rps_irq;
	unsigned long status;

	chained_irq_enter(chip, desc);	

	/* read the IRQ number from the RPS core */
	status = rpsa->irq_mask_status;

	/* convert the RPS interrupt number into a system interrupt number */
	rps_irq = find_first_bit(&status, BITS_PER_LONG);
	while(rps_irq < BITS_PER_LONG) {
		generic_handle_irq(OX820_RPSA_IRQ_START + rps_irq);
		rps_irq = find_next_bit(&status, BITS_PER_LONG, rps_irq + 1);
	}

	chained_irq_exit(chip, desc);
}

void __init ox820_rps_init_irq() {
	unsigned irq;
	struct ox820_rpsa_registers_t* const rpsa = (struct ox820_rpsa_registers_t*) RPSA_BASE;
    
	printk("ox820_rps_init_irq: interrupts %d to %d\n",OX820_RPSA_IRQ_START,OX820_RPSA_IRQ_START+31);
	/* Disable all IRQs */
	rpsa->irq_disable_control = ~0;
	wmb();
    
	/* Initialise IRQ tracking structures */
	for (irq = OX820_RPSA_IRQ_START; irq < OX820_RPSA_IRQ_START + 32; irq++)
	{
		irq_set_chip_and_handler(irq, &ox820_rps_chip, handle_level_irq);
		set_irq_flags(irq, IRQF_VALID | IRQF_PROBE);
	}

	/* setup the handler */
	irq_set_chained_handler(OX820_ARM_GIC_IRQ_RPSA_IRQ, ox820_rps_irq);
}

/** 
 * induces a FIQ in the cpu number passed as a parameter
 */
void OX820_RPS_trigger_fiq(unsigned int cpu) {
	void* base[2] = {
	 	 (void* )RPSA_BASE,
	 	 (void* )RPSC_BASE
	};
    
	*((volatile unsigned long*)(base[cpu] + RPS_FIQ_IRQ_TO_FIQ)) = 1;
	wmb();
	*((volatile unsigned long*)(base[cpu] + RPS_FIQ_ENABLE)) = 1;
	wmb();
	*((volatile unsigned long*)(base[cpu] + RPS_IRQ_SOFT)) = 2;
	wmb();
}

/* clears FIQ mode for the interrupt specified, those interrupts will now 
be forwarded on the IRQ output line */
void OX820_RPS_clear_fiq(unsigned int cpu) {
	void* base[2] = {
	 	 (void* )RPSA_BASE,
	 	 (void* )RPSC_BASE
	};
    
	*((volatile unsigned long*)(base[cpu] + RPS_IRQ_SOFT)) = 0;
	wmb();
	*((volatile unsigned long*)(base[cpu] + RPS_FIQ_DISABLE)) = 1;
   	wmb();
}
