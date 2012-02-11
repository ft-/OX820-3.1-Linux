/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _ox820_hw_rpsc_h
#define _ox820_hw_rpsc_h

struct ox820_rpsc_registers_t
{
	volatile u32 irq_mask_status;           /* +0x0000 */
	volatile u32 irq_raw_status;            /* +0x0004 */
	u32 irq_enable_control;         	/* +0x0008 */
	u32 irq_disable_control;        	/* +0x000C */
	u32 software_irq;               	/* +0x0010 */
	u32 reserved_0[59];             	/* +0x0014 */
	u32 fiq_mask_source;            	/* +0x0100 */
	u32 fiq_raw_source;             	/* +0x0104 */
	u32 fiq_enable_control;        		/* +0x0108 */
	u32 fiq_disable_control;        	/* +0x010C */
	u32 fiq_select;                 	/* +0x0110 */
	u32 reserved_1[59];             	/* +0x0114 */
	u32 timer1_load;                	/* +0x0200 */
	volatile u32 timer1_current_count;      /* +0x0204 */
	u32 timer1_control;             	/* +0x0208 */
	u32 timer1_clear_interrupt;     	/* +0x020C */
	u32 reserved_2[4];              	/* +0x0210 */
	u32 timer2_load;                	/* +0x0220 */
	volatile u32 timer2_current_count;      /* +0x0224 */
	u32 timer2_control;             	/* +0x0228 */
	u32 timer2_clear_interrupt;     	/* +0x022C */
	u32 reserved_3[100];            	/* +0x0230 */
	u32 chip_configuration;         	/* +0x03C0 */
	u32 reserved_4[14];             	/* +0x03C4 */
	u32 chip_id;                    	/* +0x03FC */
};

/* IRQ/FIQ definitions */
#define BIT_OX820_RPSC_IRQ_UNUSED           0
#define BIT_OX820_RPSC_IRQ_SOFTWARE_IRQ     1
#define BIT_OX820_RPSC_IRQ_ARM_COMMRX       2
#define BIT_OX820_RPSC_IRQ_ARM_COMMTX       3
#define BIT_OX820_RPSC_IRQ_RPSC_TIMER1      4
#define BIT_OX820_RPSC_IRQ_RPSC_TIMER2      5
#define BIT_OX820_RPSC_IRQ_IRRX             6
#define BIT_OX820_RPSC_IRQ_USB_HOST         7
#define BIT_OX820_RPSC_IRQ_GMAC_A           8
#define BIT_OX820_RPSC_IRQ_GMAC_B           9
#define BIT_OX820_RPSC_IRQ_SEMA_A           10
#define BIT_OX820_RPSC_IRQ_SEMA_B           11
#define BIT_OX820_RPSC_IRQ_SEMA_C           12
#define BIT_OX820_RPSC_IRQ_SGDMA_CHANNEL0   13
#define BIT_OX820_RPSC_IRQ_SGDMA_CHANNEL1   14
#define BIT_OX820_RPSC_IRQ_SGDMA_CHANNEL2   15
#define BIT_OX820_RPSC_IRQ_SGDMA_CHANNEL3   16
#define BIT_OX820_RPSC_IRQ_GMAC_A_PMT       17
#define BIT_OX820_RPSC_IRQ_SATA             18
#define BIT_OX820_RPSC_IRQ_PCIE_A           19
#define BIT_OX820_RPSC_IRQ_PCIE_B           20
#define BIT_OX820_RPSC_IRQ_GPIO_A           21
#define BIT_OX820_RPSC_IRQ_GPIO_B           22
#define BIT_OX820_RPSC_IRQ_UART_A           23
#define BIT_OX820_RPSC_IRQ_UART_B           24
#define BIT_OX820_RPSC_IRQ_AUDIO            25
#define BIT_OX820_RPSC_IRQ_AUDIO_ERROR      26
#define BIT_OX820_RPSC_IRQ_VIDEO_OUTPUT     27
#define BIT_OX820_RPSC_IRQ_GMAC_B_PMT       28
#define BIT_OX820_RPSC_IRQ_SD               29
#define BIT_OX820_RPSC_IRQ_USBDEV           30
#define BIT_OX820_RPSC_IRQ_RESERVED         31

#define MSK_OX820_RPSC_IRQ_UNUSED           0x00000001
#define MSK_OX820_RPSC_IRQ_SOFTWARE_IRQ     0x00000002
#define MSK_OX820_RPSC_IRQ_ARM_COMMRX       0x00000004
#define MSK_OX820_RPSC_IRQ_ARM_COMMTX       0x00000008
#define MSK_OX820_RPSC_IRQ_RPSC_TIMER1      0x00000010
#define MSK_OX820_RPSC_IRQ_RPSC_TIMER2      0x00000020
#define MSK_OX820_RPSC_IRQ_IRRX             0x00000040
#define MSK_OX820_RPSC_IRQ_USB_HOST         0x00000080
#define MSK_OX820_RPSC_IRQ_GMAC_A           0x00000100
#define MSK_OX820_RPSC_IRQ_GMAC_B           0x00000200
#define MSK_OX820_RPSC_IRQ_SEMA_A           0x00000400
#define MSK_OX820_RPSC_IRQ_SEMA_B           0x00000800
#define MSK_OX820_RPSC_IRQ_SEMA_C           0x00001000
#define MSK_OX820_RPSC_IRQ_SGDMA_CHANNEL0   0x00002000
#define MSK_OX820_RPSC_IRQ_SGDMA_CHANNEL1   0x00004000
#define MSK_OX820_RPSC_IRQ_SGDMA_CHANNEL2   0x00008000
#define MSK_OX820_RPSC_IRQ_SGDMA_CHANNEL3   0x00010000
#define MSK_OX820_RPSC_IRQ_GMAC_A_PMT       0x00020000
#define MSK_OX820_RPSC_IRQ_SATA             0x00040000
#define MSK_OX820_RPSC_IRQ_PCIE_A           0x00080000
#define MSK_OX820_RPSC_IRQ_PCIE_B           0x00100000
#define MSK_OX820_RPSC_IRQ_GPIO_A           0x00200000
#define MSK_OX820_RPSC_IRQ_GPIO_B           0x00400000
#define MSK_OX820_RPSC_IRQ_UART_A           0x00800000
#define MSK_OX820_RPSC_IRQ_UART_B           0x01000000
#define MSK_OX820_RPSC_IRQ_AUDIO            0x02000000
#define MSK_OX820_RPSC_IRQ_AUDIO_ERROR      0x04000000
#define MSK_OX820_RPSC_IRQ_VIDEO_OUTPUT     0x08000000
#define MSK_OX820_RPSC_IRQ_GMAC_B_PMT       0x10000000
#define MSK_OX820_RPSC_IRQ_SD               0x20000000
#define MSK_OX820_RPSC_IRQ_USBDEV           0x40000000
#define MSK_OX820_RPSC_IRQ_RESERVED         0x80000000

/* Timer Control */
#define MSK_OX820_RPSC_TIMER_ENABLE             0x80
#define BIT_OX820_RPSC_TIMER_ENABLE             7

#define MSK_OX820_RPSC_TIMER_RELOAD_MODE        0x40
#define BIT_OX820_RPSC_TIMER_RELOAD_MODE        6

#define MSK_OX820_RPSC_TIMER_PRESCALE_DIVIDER   0x0C
#define BIT_OX820_RPSC_TIMER_PRESCALE_DIVIDER   2

#endif
