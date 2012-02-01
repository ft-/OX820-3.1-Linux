/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _ox820_hw_pciephy_h
#define _ox820_hw_pciephy_h

#include <linux/types.h>

struct ox820_pcie_elbi_registers_t
{
	volatile u32 pim0_mem_addr_limit;
	u32 reserved_0;
	volatile u32 pim1_mem_addr_limit;
	u32 reserved_1;
	volatile u32 pim0_mem_addr_start;
	u32 reserved_2;
	volatile u32 pim1_mem_addr_start;
	u32 reserved_3;
	volatile u32 pim_io_addr_offset;
	u32 reserved_4[54];
	volatile u32 ib_addr_xlate_enable;
};

#define MSK_OX820_PCIE_ELBI_XLATE_ENABLE		0x00000001
#define BIT_OX820_PCIE_ELBI_XLATE_ENABLE		0
#define VAL_OX820_PCIE_ELBI_XLATE_ENABLE_ON		0x00000001
#define VAL_OX820_PCIE_ELBI_XLATE_ENABLE_OFF		0x00000000

#endif
