/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _ox820_hw_sata_h
#define _ox820_hw_sata_h

#include <linux/types.h>
#include <mach/hw/dma.h>
#include <mach/hw/sgdma.h>
#include <mach/hw/cipher.h>

struct ox820_sata_port_registers_t
{
	u32     orb1;                           /* +0x0000 */
	u32     orb2;                           /* +0x0004 */
	u32     orb3;                           /* +0x0008 */
	u32     orb4;                           /* +0x000C */
	u32     orb5;                           /* +0x0010 */
	u32     reserved_0;                     /* +0x0014 */
	u32     fis_ctrl;                       /* +0x0018 */
	u32     fis_data;                       /* +0x001C */
	u32     rbc1;                           /* +0x0020 */
	u32     rbc2;                           /* +0x0024 */
	u32     rbc3;                           /* +0x0028 */
	u32     rbc4;                           /* +0x002C */
	volatile u32     int_ctrl_status;       /* +0x0030 */
	u32     int_enable_set;                 /* +0x0034 */
	u32     int_enable_clear;               /* +0x0038 */
	u32     version;                        /* +0x003C */
	u32     reserved_1[3];                  /* +0x0040 */
	u32     sactive;                        /* +0x004C */
	u32     active_tag;                     /* +0x0050 */
	u32     reserved_2[2];                  /* +0x0054 */
	u32     sata_ctrl;                      /* +0x005C */
	u32     command;                        /* +0x0060 */
	u32     reserved_3;                     /* +0x0064 */
	u32     port_ctrl;                      /* +0x0068 */
	u32     drive_ctrl;                     /* +0x006C */
	u32     link_async_data;                /* +0x0070 */
	u32     link_async_r_addr;              /* +0x0074 */
	u32     link_async_w_addr;              /* +0x0078 */
	u32     link_async_ctrl;                /* +0x007C */
	u32     win_low_3100;                   /* +0x0080 */
    	u32     win_low_4732;                   /* +0x0084 */
    	u32     win_high_3100;                  /* +0x0088 */
    	u32     win_high_4732;                  /* +0x008C */
    	u32     win_ctrl_zero;                  /* +0x0090 */
    	u32     win_ctrl_one;                   /* +0x0094 */
    	u32     win_ctrl_two;                   /* +0x0098 */
    	u32     reserved_4;                     /* +0x009C */
    	u32     port_ctrl2;                     /* +0x00A0 */
    	u32     reserved_5;                     /* +0x00A4 */
    	u32     pio_size;                       /* +0x00A8 */
    	u32     reserved_6;                     /* +0x00AC */
    	u32     backup1;                        /* +0x00B0 */
    	u32     backup2;                        /* +0x00B4 */
    	u32     backup3;                        /* +0x00B8 */
    	u32     backup4;                        /* +0x00BC */
    	u32     reserved_7[4];                  /* +0x00C0 */
    	u32     mse_info1;                      /* +0x00D0 */
    	u32     mse_info2;                      /* +0x00D4 */
    	u32     mse_info3;                      /* +0x00D8 */
};

/* OX820 SATA DMA is already defined as ox820_dma_channel_registers_t */
#define ox820_sata_dma_port_registers_t ox820_dma_channel_registers_t

/* OX820 SATA SGDMA is already defined as ox820_sgdma_channel_registers_t */
#define ox820_sata_sgdma_port_registers_t ox820_sgdma_channel_registers_t

/* OX820 SATA Cipher is already defined as ox820_cipher_registers_t */
#define ox820_sata_cipher_registers_t ox820_cipher_registers_t

struct ox820_sata_raid_port_registers_t
{
	u32     orb1;                           /* +0x0000 */
	u32     orb2;                           /* +0x0004 */
	u32     orb3;                           /* +0x0008 */
	u32     orb4;                           /* +0x000C */
	u32     orb5;                           /* +0x0010 */
	u32     reserved_0;                     /* +0x0014 */
	u32     fis_ctrl;                       /* +0x0018 */
	u32     fis_data;                       /* +0x001C */
	u32     rbc1;                           /* +0x0020 */
	u32     rbc2;                           /* +0x0024 */
	u32     rbc3;                           /* +0x0028 */
	u32     rbc4;                           /* +0x002C */
	volatile u32     int_ctrl_status;       /* +0x0030 */
	u32     int_enable_set;                 /* +0x0034 */
	u32     int_enable_clear;               /* +0x0038 */
	u32     version;                        /* +0x003C */
	u32     reserved_1[7];                  /* +0x0040 */
	u32     sata_ctrl;                      /* +0x005C */
	u32     command;                        /* +0x0060 */
	u32     reserved_2[7];                  /* +0x0064 */
	u32     win_low_3100;                   /* +0x0080 */
	u32     win_low_4732;                   /* +0x0084 */
	u32     win_high_3100;                  /* +0x0088 */
	u32     win_high_4732;                  /* +0x008C */
	u32     win_ctrl_zero;                  /* +0x0090 */
	u32     win_ctrl_one;                   /* +0x0094 */
	u32     win_ctrl_two;                   /* +0x0098 */
	u32     reserved_3[5];                  /* +0x009C */
	u32     backup1;                        /* +0x00B0 */
	u32     backup2;                        /* +0x00B4 */
	u32     backup3;                        /* +0x00B8 */
	u32     backup4;                        /* +0x00BC */
};

#endif
