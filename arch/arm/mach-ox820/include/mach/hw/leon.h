/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _ox820_hw_leon_h
#define _ox820_hw_leon_h

#include <linux/types.h>

struct ox820_leon_registers_t
{
	u32     reserved_0[5];
	u32     cache_ctrl;
	u32     pwrdn_ctrl;
};

/* cache_ctrl */
#define MSK_OX820_LEON_CACHE_CTRL_DSNOOP        0x00800000
#define BIT_OX820_LEON_CACHE_CTRL_DSNOOP        23

#define MSK_OX820_LEON_CACHE_CTRL_DFLUSH        0x00400000
#define BIT_OX820_LEON_CACHE_CTRL_DFLUSH        22

#define MSK_OX820_LEON_CACHE_CTRL_IFLUSH        0x00200000
#define BIT_OX820_LEON_CACHE_CTRL_IFLUSH        21

#define MSK_OX820_LEON_CACHE_CTRL_IB            0x00010000
#define BIT_OX820_LEON_CACHE_CTRL_IB            16

#define MSK_OX820_LEON_CACHE_CTRL_DFRZ          0x00000020
#define BIT_OX820_LEON_CACHE_CTRL_DFRZ          5

#define MSK_OX820_LEON_CACHE_CTRL_IFRZ          0x00000010
#define BIT_OX820_LEON_CACHE_CTRL_IFRZ          4

#define MSK_OX820_LEON_CACHE_CTRL_DCS           0x0000000C
#define BIT_OX820_LEON_CACHE_CTRL_DCS           2

#define MSK_OX820_LEON_CACHE_CTRL_ICS           0x00000003
#define BIT_OX820_LEON_CACHE_CTRL_ICS           0

#endif
