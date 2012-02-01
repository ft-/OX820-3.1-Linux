/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _ox820_hw_dma_h
#define _ox820_hw_dma_h

#include <linux/types.h>

/* One per channel */
struct ox820_dma_channel_registers_t
{
	u32     ctrl_stat;          /* +0x0000 */
	u32     base_s_addr;        /* +0x0004 */
	u32     base_des_addr;      /* +0x0008 */
	u32     byte_count;         /* +0x000C */
	u32     current_s_addr;     /* +0x0010 */
	u32     current_des_addr;   /* +0x0014 */
	u32     current_byte_count; /* +0x0018 */
	u32     int_reg_dma_ver;    /* +0x001C */
};

struct ox820_dma_registers_t
{
	struct ox820_dma_channel_registers_t channel[4];
};

/* ctrl_stat */
#define MSK_OX820_DMA_CTRL_STAT_CLEAR_INT_REG_EN            0x40000000
#define BIT_OX820_DMA_CTRL_STAT_CLEAR_INT_REG_EN            30

#define MSK_OX820_DMA_CTRL_STAT_STARVE_LOW_PRIO             0x20000000
#define BIT_OX820_DMA_CTRL_STAT_STARVE_LOW_PRIO             29

#define MSK_OX820_DMA_CTRL_STAT_FIXED_ADDR_D                0x10000000
#define BIT_OX820_DMA_CTRL_STAT_FIXED_ADDR_D                28

#define MSK_OX820_DMA_CTRL_STAT_FIXED_ADDR_S                0x08000000
#define BIT_OX820_DMA_CTRL_STAT_FIXED_ADDR_S                27

#define MSK_OX820_DMA_CTRL_STAT_INT_ENABLE                  0x04000000
#define BIT_OX820_DMA_CTRL_STAT_INT_ENABLE                  26

#define MSK_OX820_DMA_CTRL_STAT_PAUSE_DMA                   0x02000000
#define BIT_OX820_DMA_CTRL_STAT_PAUSE_DMA                   25

#define MSK_OX820_DMA_CTRL_STAT_DEVICE_TYPE_D               0x01C00000
#define BIT_OX820_DMA_CTRL_STAT_DEVICE_TYPE_D               22
#define VAL_OX820_DMA_CTRL_STAT_DEVICE_TYPE_D_8BIT          0x00000000
#define VAL_OX820_DMA_CTRL_STAT_DEVICE_TYPE_D_16BIT         0x00400000
#define VAL_OX820_DMA_CTRL_STAT_DEVICE_TYPE_D_32BIT         0x00800000

#define MSK_OX820_DMA_CTRL_STAT_DEVICE_TYPE_S               0x00380000
#define BIT_OX820_DMA_CTRL_STAT_DEVICE_TYPE_S               19
#define VAL_OX820_DMA_CTRL_STAT_DEVICE_TYPE_S_8BIT          0x00000000
#define VAL_OX820_DMA_CTRL_STAT_DEVICE_TYPE_S_16BIT         0x00080000
#define VAL_OX820_DMA_CTRL_STAT_DEVICE_TYPE_S_32BIT         0x00100000

#define MSK_OX820_DMA_CTRL_STAT_MODE_B                      0x00040000
#define BIT_OX820_DMA_CTRL_STAT_MODE_B                      18

#define MSK_OX820_DMA_CTRL_STAT_MODE_A                      0x00020000
#define BIT_OX820_DMA_CTRL_STAT_MODE_A                      17

#define MSK_OX820_DMA_CTRL_STAT_INC_ADDR_D                  0x00010000
#define BIT_OX820_DMA_CTRL_STAT_INC_ADDR_D                  16

#define MSK_OX820_DMA_CTRL_STAT_INC_ADDR_S                  0x00008000
#define BIT_OX820_DMA_CTRL_STAT_INC_ADDR_S                  15

#define MSK_OX820_DMA_CTRL_STAT_DIRECTION                   0x00006000
#define BIT_OX820_DMA_CTRL_STAT_DIRECTION                   13
#define VAL_OX820_DMA_CTRL_STAT_DIRECTION_A_TO_A            0x00000000
#define VAL_OX820_DMA_CTRL_STAT_DIRECTION_B_TO_A            0x00002000
#define VAL_OX820_DMA_CTRL_STAT_DIRECTION_A_TO_B            0x00004000
#define VAL_OX820_DMA_CTRL_STAT_DIRECTION_B_TO_B            0x00006000

#define MSK_OX820_DMA_CTRL_STAT_CH_RESET                    0x00001000
#define BIT_OX820_DMA_CTRL_STAT_CH_RESET                    12

#define MSK_OX820_DMA_CTRL_STAT_NEXT_FREE                   0x00000800
#define BIT_OX820_DMA_CTRL_STAT_NEXT_FREE                   11

#define MSK_OX820_DMA_CTRL_STAT_INT                         0x00000400
#define BIT_OX820_DMA_CTRL_STAT_INT                         10

#define MSK_OX820_DMA_CTRL_STAT_SFT_D_DREQ                  0x000003C0
#define BIT_OX820_DMA_CTRL_STAT_SFT_D_DREQ                  6
#define VAL_OX820_DMA_CTRL_STAT_SFT_D_DREQ_SD_READ          0x00000000
#define VAL_OX820_DMA_CTRL_STAT_SFT_D_DREQ_SD_WRITE         0x00000040
#define VAL_OX820_DMA_CTRL_STAT_SFT_D_DREQ_CIPHER_READ      0x00000080
#define VAL_OX820_DMA_CTRL_STAT_SFT_D_DREQ_CIPHER_WRITE     0x000000C0
#define VAL_OX820_DMA_CTRL_STAT_SFT_D_DREQ_AUDIO_READ       0x00000100
#define VAL_OX820_DMA_CTRL_STAT_SFT_D_DREQ_AUDIO_WRITE      0x00000140
#define VAL_OX820_DMA_CTRL_STAT_SFT_D_DREQ_MEMORY           0x000003C0

#define MSK_OX820_DMA_CTRL_STAT_SFT_S_DREQ                  0x0000003C
#define BIT_OX820_DMA_CTRL_STAT_SFT_S_DREQ                  2
#define VAL_OX820_DMA_CTRL_STAT_SFT_S_DREQ_SD_READ          0x00000000
#define VAL_OX820_DMA_CTRL_STAT_SFT_S_DREQ_SD_WRITE         0x00000004
#define VAL_OX820_DMA_CTRL_STAT_SFT_S_DREQ_CIPHER_READ      0x00000008
#define VAL_OX820_DMA_CTRL_STAT_SFT_S_DREQ_CIPHER_WRITE     0x0000000C
#define VAL_OX820_DMA_CTRL_STAT_SFT_S_DREQ_AUDIO_READ       0x00000010
#define VAL_OX820_DMA_CTRL_STAT_SFT_S_DREQ_AUDIO_WRITE      0x00000014
#define VAL_OX820_DMA_CTRL_STAT_SFT_S_DREQ_MEMORY           0x0000003C

#define MSK_OX820_DMA_CTRL_STAT_DMA_IN_PROGRESS             0x00000002
#define BIT_OX820_DMA_CTRL_STAT_DMA_IN_PROGRESS             1

#define MSK_OX820_DMA_CTRL_STAT_FAIR_SHARE_AHB              0x00000001
#define BIT_OX820_DMA_CTRL_STAT_FAIR_SHARE_AHB              0

/* byte_count */
#define MSK_OX820_DMA_BYTE_COUNT_WR_EOT                     0x40000000
#define BIT_OX820_DMA_BYTE_COUNT_WR_EOT                     30

#define MSK_OX820_DMA_BYTE_COUNT_HPROT_SET                  0x20000000
#define BIT_OX820_DMA_BYTE_COUNT_HPROT_SET                  29

#define MSK_OX820_DMA_BYTE_COUNT_FIXED_INCR                 0x10000000
#define BIT_OX820_DMA_BYTE_COUNT_FIXED_INCR                 28

#define MSK_OX820_DMA_BYTE_COUNT_BURST_MODE_A               0x0C000000
#define BIT_OX820_DMA_BYTE_COUNT_BURST_MODE_A               26
#define VAL_OX820_DMA_BYTE_COUNT_BURST_MODE_A_INCR4         0x00000000
#define VAL_OX820_DMA_BYTE_COUNT_BURST_MODE_A_INCR8         0x04000000
#define VAL_OX820_DMA_BYTE_COUNT_BURST_MODE_A_INCR16        0x08000000

#define MSK_OX820_DMA_BYTE_COUNT_BURST_MODE_A               0x03000000
#define BIT_OX820_DMA_BYTE_COUNT_BURST_MODE_A               24
#define VAL_OX820_DMA_BYTE_COUNT_BURST_MODE_A_INCR4         0x00000000
#define VAL_OX820_DMA_BYTE_COUNT_BURST_MODE_A_INCR8         0x01000000
#define VAL_OX820_DMA_BYTE_COUNT_BURST_MODE_A_INCR16        0x02000000

#define MSK_OX820_DMA_BYTE_COUNT_BYTE_COUNT                 0x003FFFFF
#define BIT_OX820_DMA_BYTE_COUNT_BYTE_COUNT                 0

#endif
