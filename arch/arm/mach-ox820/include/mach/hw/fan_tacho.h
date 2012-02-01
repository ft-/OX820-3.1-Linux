/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _ox820_hw_fan_tacho_h
#define _ox820_hw_fan_tacho_h

#include <linux/types.h>

struct ox820_fan_tacho_registers_t
{
	u32 fan_tacho_counter;
	u32 thermistor_rc_counter;
	u32 thermistor_control;
	u32 clock_divider;
	u32 fan_tacho_control;
	u32 fan_one_shot_control;
	u32 fan_motor_pwm_divider;
	u32 fan_motor_pwm_value;
};

#endif
