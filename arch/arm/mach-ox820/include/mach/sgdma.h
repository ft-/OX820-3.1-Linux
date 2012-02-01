/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef _ox820_mach_sgdma_h
#define _ox820_mach_sgdma_h

#include <linux/types.h>
#include <mach/hw/sgdma.h>
#include <linux/dma-mapping.h>

struct ox820_sgdma_request_entry_t
{
	struct ox820_sgdma_sg_entry_t		hw;
	void*					vaddr;
};

struct ox820_sgdma_request_t
{
	struct ox820_sgdma_sg_info_t		hw;
	struct ox820_sgdma_request_t*		next;
	dma_addr_t				sginfo_dmaptr;
	u32					num_srcentries;
	u32					num_dstentries;
	struct ox820_sgdma_request_entry_t*	srcentries;
	struct ox820_sgdma_request_entry_t*	dstentries;
	struct ox820_sgdma_request_entry_t	entries[];
};

/**************************************/
/* Basic function for SGDMA request blocks */
/* entries[x].hw.addr and entries[x].hw.length must be set up on caller's side */
struct ox820_sgdma_request_t* ox820_sgdma_alloc_request(struct device* dev, gfp_t gfp_flags, u32 qualifier, u32 control, u32 num_srcentries, u32 num_dstentries);

void ox820_sgdma_free_request(struct device* dev, struct ox820_sgdma_request_t*);

#endif
