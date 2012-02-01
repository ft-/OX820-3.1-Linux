/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _ox820_hw_gpio_h
#define _ox820_hw_gpio_h

#include <linux/types.h>

struct ox820_gpio_pwm_registers_t
{
	u32 pwm_value;
	u32 rr;
};

struct ox820_gpio_registers_t
{
	volatile u32 input;			/* +0x0000 hardware input so it is volatile */
	u32 output_enable;			/* +0x0004 */
	u32 irq_enable_mask;			/* +0x0008 */
	volatile u32 irq_event;			/* +0x000C / needed since acknowledgement field / writing back same value */
	u32 output;				/* +0x0010 */
	u32 output_set;				/* +0x0014 */
	u32 output_clear;			/* +0x0018 */
	u32 output_enable_set;			/* +0x001C */
	u32 output_enable_clear;		/* +0x0020 */
	u32 debounce_enable;			/* +0x0024 */
	u32 rising_edge_act_high_irq_enable;	/* +0x0028 */
	u32 falling_edge_act_low_irq_enable;	/* +0x002C */
	volatile u32 rising_edge_irq_events;	/* +0x0030 may change when read multiple times so it is volatile */
	volatile u32 falling_edge_irq_events;	/* +0x0034 may change when read multiple times so it is volatile */
	u32 level_interrupt_enable;		/* +0x0038 */
	volatile u32 irq_status;		/* +0x003C may change when read multiple times so it is volatile */
	u32 invert_enable;			/* +0x0040 */
	u32 core_version;			/* +0x0044 */
	u32 clock_divider;			/* +0x0048 */
	u32 pwm_irq_timer;			/* +0x004C */
	u32 pull_enable;			/* +0x0050 */
	u32 pull_sense;				/* +0x0054 */
	u32 reserved_0[10];			/* +0x0058 */
	struct ox820_gpio_pwm_registers_t pwm[32]; /* +0x0080 */
};

#endif
