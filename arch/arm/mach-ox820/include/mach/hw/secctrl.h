/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _ox820_hw_secctrl_h
#define _ox820_hw_secctrl_h

#include <linux/types.h>

struct ox820_secctrl_registers_t
{
	u32     reserved_0[5];              /* +0x0000 */
	u32     mfb_secsel_ctrl;            /* +0x0014 */
	u32     reserved_1[20];             /* +0x0018 */
	u32     leon_ctrl;                  /* +0x0068 */
	u32     reserved_2[8];              /* +0x006C */
	u32     mfb_tersel_ctrl;            /* +0x008C */
	u32     reserved_3;                 /* +0x0090 */
	u32     mfb_quatsel_ctrl;           /* +0x0094 */
	u32     secure_ctrl;                /* +0x0098 */
	u32     mfb_debugsel_ctrl;          /* +0x009C */
	u32     reserved_4;                 /* +0x00A0 */
	u32     mfb_altsel_ctrl;            /* +0x00A4 */
	u32     reserved_5;                 /* +0x00A8 */
	u32     mfb_pullup_ctrl;            /* +0x00AC */
	u32     reserved_6[16];             /* +0x00B0 */
	u32     leon_debug_ctrl;            /* +0x00F0 */
	u32     reserved_7;                 /* +0x00F4 */
	u32     pllb_div_ctrl;              /* +0x00F8 */
	u32     reserved_8[57];             /* +0x00FC */
	u32     otp_ctrl;                   /* +0x01E0 */
	u32     otp_rdata;                  /* +0x01E4 */
	u32     reserved_9[2];              /* +0x01E8 */
	volatile u32 pllb_ctrl[4];          /* +0x01F0 */
};

#define MSK_OX820_SECCTRL_PLLB_CTRL0_PLLB_BYPASS	0x00000002
#define BIT_OX820_SECCTRL_PLLB_CTRL0_PLLB_BYPASS	1

/* leon_ctrl */
#define MSK_OX820_SECCTRL_LEON_CTRL_START_ADDR		0xFFFFFFFC
#define BIT_OX820_SECCTRL_LEON_CTRL_START_ADDR		2
#define MSK_OX820_SECCTRL_LEON_CTRL_DOUBLE_CLK		0x00000002
#define BIT_OX820_SECCTRL_LEON_CTRL_DOUBLE_CLK		1
#define MSK_OX820_SECCTRL_LEON_CTRL_PROMOTE_IRQ		0x00000001
#define BIT_OX820_SECCTRL_LEON_CTRL_PROMOTE_IRQ		0
#endif
