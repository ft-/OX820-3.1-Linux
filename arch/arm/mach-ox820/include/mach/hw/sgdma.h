/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _ox820_hw_sgdma_h
#define _ox820_hw_sgdma_h

#include <linux/types.h>
#include <linux/dma-mapping.h>

struct ox820_sgdma_channel_registers_t
{
	u32 control;                /* +0x0000 */
	u32 status;                 /* +0x0004 */
	u32 request_pointer;        /* +0x0008 */
	u32 sub_block_resets;       /* +0x000C */
};

struct ox820_sgdma_registers_t
{
    struct ox820_sgdma_channel_registers_t channel[4];
};

/* control */
#define MSK_OX820_SGDMA_CONTROL_PRD_TABLE       0x00000010
#define BIT_OX820_SGDMA_CONTROL_PRD_TABLE       4

#define MSK_OX820_SGDMA_CONTROL_CLR_LAST_IRQ    0x00000008
#define BIT_OX820_SGDMA_CONTROL_CLR_LAST_IRQ    3

#define MSK_OX820_SGDMA_CONTROL_BURST_TYPE      0x00000004
#define BIT_OX820_SGDMA_CONTROL_BURST_TYPE      2

#define MSK_OX820_SGDMA_CONTROL_QUEUING_ENABLE  0x00000002
#define BIT_OX820_SGDMA_CONTROL_QUEUING_ENABLE  1

#define MSK_OX820_SGDMA_CONTROL_START           0x00000001
#define BIT_OX820_SGDMA_CONTROL_START           0

/* status */
#define MSK_OX820_SGDMA_STATUS_BUSY             0x00000080
#define BIT_OX820_SGDMA_STATUS_BUSY             7

#define MSK_OX820_SGDMA_STATUS_ERRORCODE        0x0000003F
#define BIT_OX820_SGDMA_STATUS_ERRORCODE        0

/* sub_block_resets */
#define MSK_OX820_SGDMA_SBR_AHB_MASTER_RESET    0x00000004
#define BIT_OX820_SGDMA_SBR_AHB_MASTER_RESET    2

#define MSK_OX820_SGDMA_SBR_ARBITER_RESET       0x00000002
#define BIT_OX820_SGDMA_SBR_ARBITER_RESET       1

#define MSK_OX820_SGDMA_SBR_CONTROL_RESET       0x00000001
#define BIT_OX820_SGDMA_SBR_CONTROL_RESET       0

/* following structures are the hw-specific structures.
 * for additional data make them be at the start of that structure
 */
struct ox820_sgdma_sg_entry_t
{
    dma_addr_t              addr;
    unsigned long           length;
    dma_addr_t              next;
};

struct ox820_sgdma_sg_info_t
{
    unsigned long           qualifier;
    unsigned long           control;
    dma_addr_t              src_entries;
    dma_addr_t              dst_entries;
};

/* qualifier */
#define MSK_OX820_DMA_SG_QUALIFIER_VAL          0x0000FFFF
#define BIT_OX820_DMA_SG_QUALIFIER_VAL          0
#define MSK_OX820_DMA_SG_QUALIFIER_DST_EOT      0x00030000
#define BIT_OX820_DMA_SG_QUALIFIER_DST_EOT      16
#define MSK_OX820_DMA_SG_QUALIFIER_SRC_EOT      0x00300000
#define BIT_OX820_DMA_SG_QUALIFIER_SRC_EOT      20
#define MSK_OX820_DMA_SG_QUALIFIER_CHANNEL      0xFF000000
#define BIT_OX820_DMA_SG_QUALIFIER_CHANNEL      24

#endif
