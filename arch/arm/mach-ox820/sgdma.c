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

#include <asm-generic/scatterlist.h>
#include <mach/sgdma.h>
#include <mach/hw/sgdma.h>
#include <linux/device.h>

/******************************************************************************/
/* Basic functions for creating SGDMA request blocks */
struct ox820_sgdma_request_t* ox820_sgdma_alloc_request(struct device* dev, gfp_t gfp_flags, u32 qualifier, u32 control, u32 num_srcentries, u32 num_dstentries)
{
    dma_addr_t sgdma_req_dma;
    dma_addr_t sgdma_entries;
    struct ox820_sgdma_request_t* sgdma_req;
    u32 idx;
    u32 size = sizeof(struct ox820_sgdma_request_t) + (num_srcentries + num_dstentries) * sizeof(struct ox820_sgdma_request_entry_t);
    
    sgdma_req = dma_alloc_coherent(dev, size, &sgdma_req_dma, gfp_flags);
    if(NULL != sgdma_req) {
        sgdma_entries = sgdma_req_dma + sizeof(struct ox820_sgdma_request_t);
        for(idx = 0; idx < num_srcentries - 1; ++idx) {
            sgdma_req->entries[idx].hw.next = sgdma_entries + (idx + 1) * sizeof(struct ox820_sgdma_request_entry_t);
        }
        sgdma_req->entries[idx].hw.next = 0;
        for(++idx; idx < num_srcentries + num_dstentries - 1; ++idx) {
            sgdma_req->entries[idx].hw.next = sgdma_entries + (idx + 1) * sizeof(struct ox820_sgdma_request_entry_t);
        }
        sgdma_req->entries[idx].hw.next = 0;
        
        sgdma_req->sginfo_dmaptr = sgdma_req_dma;
        sgdma_req->hw.control = control;
        sgdma_req->hw.qualifier = qualifier;
        sgdma_req->hw.src_entries = sgdma_entries;
        sgdma_req->hw.dst_entries = sgdma_entries + num_srcentries * sizeof(struct ox820_sgdma_request_entry_t);
    }
    
    return sgdma_req;
}

void ox820_sgdma_free_request(struct device* dev, struct ox820_sgdma_request_t* sgdma_req)
{
    u32 size = sizeof(struct ox820_sgdma_request_t) + (sgdma_req->num_srcentries + sgdma_req->num_dstentries) * sizeof(struct ox820_sgdma_request_entry_t);
    dma_free_coherent(dev, size, sgdma_req, sgdma_req->sginfo_dmaptr);
}
