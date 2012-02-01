/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _ox820_hw_cipher_h
#define _ox820_hw_cipher_h

#include <linux/types.h>

struct ox820_cipher_registers_t
{
	u32 control;		/* +0x0000 */
	u32 status;		/* +0x0004 */
	u32 reserved_0[2];	/* +0x0008 */
	u32 key_1[8];		/* +0x0010 */
	u32 key_2[8];		/* +0x0030 */
	u32 reserved_1[8];	/* +0x0050 */
	u32 rx_data_in;		/* +0x0070 */
	u32 reserved_2[3];	/* +0x0074 */
	u32 tx_data_out;	/* +0x0080 */
	u32 reserved_3[3];	/* +0x0084 */
	u32 xts_iv_low;		/* +0x0090 */
	u32 xts_iv_high;	/* +0x0094 */
	u32 nrw_blks_in_wide;	/* +0x0098 */
};

/* control */
#define MSK_OX820_CIPHER_CONTROL_IV_END_SWAP        0x00002000
#define BIT_OX820_CIPHER_CONTROL_IV_END_SWAP        13

#define MSK_OX820_CIPHER_CONTROL_IV_BYTE_SWAP       0x00001000
#define BIT_OX820_CIPHER_CONTROL_IV_BYTE_SWAP       12

#define MSK_OX820_CIPHER_CONTROL_KEY_LENGTH         0x00000800
#define BIT_OX820_CIPHER_CONTROL_KEY_LENGTH         11

#define MSK_OX820_CIPHER_CONTROL_ENABLE_CTRL        0x00000400
#define BIT_OX820_CIPHER_CONTROL_ENABLE_CTRL        10

#define MSK_OX820_CIPHER_CONTROL_LBA_CTRL           0x00000200
#define BIT_OX820_CIPHER_CONTROL_LBA_CTRL           9

#define MSK_OX820_CIPHER_CONTROL_MODE               0x00000180
#define BIT_OX820_CIPHER_CONTROL_MODE               7

#define MSK_OX820_CIPHER_CONTROL_ABORT              0x00000040
#define BIT_OX820_CIPHER_CONTROL_ABORT              6

#define MSK_OX820_CIPHER_CONTROL_DIRECTION_CTRL     0x00000020
#define BIT_OX820_CIPHER_CONTROL_DIRECTION_CTRL     5

#define MSK_OX820_CIPHER_CONTROL_CPU_ENCRYPT_KEY    0x00000010
#define BIT_OX820_CIPHER_CONTROL_CPU_ENCRYPT_KEY    4

#define MSK_OX820_CIPHER_CONTROL_SW_FIFO_AC         0x00000008
#define BIT_OX820_CIPHER_CONTROL_SW_FIFO_AC         3

#define MSK_OX820_CIPHER_CONTROL_USE_KEY            0x00000004
#define BIT_OX820_CIPHER_CONTROL_USE_KEY            2

#define MSK_OX820_CIPHER_CONTROL_DIRECTION          0x00000002
#define BIT_OX820_CIPHER_CONTROL_DIRECTION          1

#define MSK_OX820_CIPHER_CONTROL_ENABLE             0x00000001
#define BIT_OX820_CIPHER_CONTROL_ENABLE             0

/* status */
#define MSK_OX820_CIPHER_STATUS_ECB_STATE           0x00000070
#define BIT_OX820_CIPHER_STATUS_ECB_STATE           4

#define MSK_OX820_CIPHER_STATUS_TX_NOT_EMPTY        0x00000008
#define BIT_OX820_CIPHER_STATUS_TX_NOT_EMPTY        3

#define MSK_OX820_CIPHER_STATUS_RX_SPACE            0x00000004
#define BIT_OX820_CIPHER_STATUS_RX_SPACE            2

#define MSK_OX820_CIPHER_STATUS_IDLE                0x00000001
#define BIT_OX820_CIPHER_STATUS_IDLE                0

#endif
