/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _ox820_hw_pciephy_h
#define _ox820_hw_pciephy_h

#include <linux/types.h>

struct ox820_pciephy_registers_t
{
	volatile u32 address_load;
	volatile u32 data_load;
	volatile u32 jtag_control;
};

#endif
