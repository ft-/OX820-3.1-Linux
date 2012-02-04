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
 *
 */
#include "ox820_gmac.h"

/*=============================================================================*/
int ox820_gmac_dma_init(struct ox820_gmac_t* gmac,
                        unsigned int num_rx_descriptors,
                        unsigned int num_tx_descriptors)
{
	unsigned int idx;

	gmac->dma.rx_descriptors_va = dma_alloc_coherent(gmac->dev,
	                                                 sizeof(struct ox820_gmac_dma_request_ctrlblock_t) * num_rx_descriptors,
	                                                 &gmac->dma.rx_descriptors_pa,
	                                                 GFP_DMA);
	if(NULL == gmac->dma.rx_descriptors_va) {
		return -ENOMEM;
	}
	gmac->dma.tx_descriptors_va = dma_alloc_coherent(gmac->dev,
	                                                 sizeof(struct ox820_gmac_dma_request_ctrlblock_t) * num_tx_descriptors,
	                                                 &gmac->dma.tx_descriptors_pa,
	                                                 GFP_DMA);
	if(NULL == gmac->dma.rx_descriptors_va) {
		dma_free_coherent(gmac->dev,
		                  sizeof(struct ox820_gmac_dma_request_ctrlblock_t) * num_rx_descriptors,
		                  gmac->dma.rx_descriptors_va,
		                  gmac->dma.rx_descriptors_pa);
		return -ENOMEM;
	}

	/* link all Rx Descriptors into our unused list for now */
	for(idx = 0; idx < num_rx_descriptors; ++idx) {
		gmac->dma.rx_descriptors_va[idx].hw.buffer2 = 0;
		gmac->dma.rx_descriptors_va[idx].hw.buffer1 = 0;
		gmac->dma.rx_descriptors_va[idx].hw.length = 0;
		gmac->dma.rx_descriptors_va[idx].hw.status = 0;
		gmac->dma.rx_descriptors_va[idx].phys_addr = gmac->dma.rx_descriptors_pa + sizeof(struct ox820_gmac_dma_request_ctrlblock_t) * idx;
		if(idx > 0) {
			gmac->dma.rx_descriptors_va[idx - 1].hw.buffer2 = gmac->dma.rx_descriptors_va[idx].phys_addr;
			gmac->dma.rx_descriptors_va[idx - 1].next = &gmac->dma.rx_descriptors_va[idx];
		}
	}
	gmac->dma.unused_rx_ctrlblocks_head = gmac->dma.rx_descriptors_va;
	gmac->dma.unused_rx_ctrlblocks_tail = &gmac->dma.rx_descriptors_va[num_rx_descriptors - 1];
	gmac->dma.incomplete_rx_ctrlblocks_head = NULL;
	gmac->dma.incomplete_rx_ctrlblocks_tail = NULL;
	gmac->dma.active_rx_ctrlblocks = NULL;

	/* link all Tx Descriptors into our free list */
	for(idx = 0; idx < num_tx_descriptors; ++idx) {
		gmac->dma.tx_descriptors_va[idx].hw.buffer2 = 0;
		gmac->dma.tx_descriptors_va[idx].hw.buffer1 = 0;
		gmac->dma.tx_descriptors_va[idx].hw.length = 0;
		gmac->dma.tx_descriptors_va[idx].hw.status = 0;
		gmac->dma.tx_descriptors_va[idx].phys_addr = gmac->dma.tx_descriptors_pa + sizeof(struct ox820_gmac_dma_request_ctrlblock_t) * idx;
		if(idx > 0) {
			gmac->dma.tx_descriptors_va[idx - 1].hw.buffer2 = gmac->dma.tx_descriptors_va[idx].phys_addr;
			gmac->dma.tx_descriptors_va[idx - 1].next = &gmac->dma.tx_descriptors_va[idx];
		}
	}
	gmac->dma.free_tx_ctrlblocks = gmac->dma.tx_descriptors_va;
	gmac->dma.num_free_tx_ctrlblocks = num_tx_descriptors;
	gmac->dma.scheduled_tx_ctrlblocks_head = NULL;
	gmac->dma.scheduled_tx_ctrlblocks_tail = NULL;
	gmac->dma.allocated_tx_descriptors = num_tx_descriptors;
	gmac->dma.allocated_rx_descriptors = num_rx_descriptors;
	spin_lock_init(&gmac->dma.tx_free_descriptors_spinlock);
	spin_lock_init(&gmac->dma.tx_schedule_descriptors_spinlock);

	return 0;
}

/*=============================================================================*/
int ox820_gmac_dma_cleanup(struct ox820_gmac_t* gmac)
{
	dma_free_coherent(gmac->dev,
	                  sizeof(struct ox820_gmac_dma_request_ctrlblock_t) * gmac->dma.allocated_tx_descriptors,
	                  gmac->dma.tx_descriptors_va,
	                  gmac->dma.tx_descriptors_pa);

	dma_free_coherent(gmac->dev,
	                  sizeof(struct ox820_gmac_dma_request_ctrlblock_t) * gmac->dma.allocated_rx_descriptors,
	                  gmac->dma.rx_descriptors_va,
	                  gmac->dma.rx_descriptors_pa);

	return 0;
}

/*=============================================================================*/
struct ox820_gmac_dma_request_ctrlblock_t*
ox820_gmac_dma_alloc_tx_descriptors(struct ox820_gmac_t* gmac,
                                    unsigned int num_descriptors)
{
	unsigned long irqflags;
	struct ox820_gmac_dma_request_ctrlblock_t* fragments = NULL;
	struct ox820_gmac_dma_request_ctrlblock_t* fragments_tail = NULL;

	if(0 == num_descriptors) {
		return NULL;
	}

	spin_lock_irqsave(&gmac->dma.tx_free_descriptors_spinlock, irqflags);

	if(gmac->dma.num_free_tx_ctrlblocks >= num_descriptors) {
		fragments = gmac->dma.free_tx_ctrlblocks;
		fragments_tail = fragments;
		fragments->prev = NULL;
		while(--num_descriptors != 0) {
			fragments_tail->next->prev = fragments_tail;
			fragments_tail = fragments_tail->next;
			fragments_tail->hw.status = 0;
			fragments_tail->last = NULL;
			fragments_tail->head = fragments;
		}
		if(fragments != fragments_tail) {
			fragments->hw.status = MSK_OX820_GMAC_DMA_TX_STATUS_FS;
			fragments_tail->hw.status |= MSK_OX820_GMAC_DMA_TX_STATUS_LS;
		} else {
			fragments->hw.status = MSK_OX820_GMAC_DMA_TX_STATUS_FS | MSK_OX820_GMAC_DMA_TX_STATUS_LS;
		}
		gmac->dma.num_free_tx_ctrlblocks -= num_descriptors;
		gmac->dma.free_tx_ctrlblocks = fragments_tail->next;
		fragments_tail->next = NULL;
		fragments_tail->last = fragments_tail; /* make last fragment significant */
		fragments->last = fragments_tail;
		fragments->dmacb_count = num_descriptors;
		wmb();
	}

	spin_unlock_irqrestore(&gmac->dma.tx_free_descriptors_spinlock, irqflags);

	return fragments;
}

/*=============================================================================*/
void
ox820_gmac_dma_free_tx_descriptors(struct ox820_gmac_t* gmac,
                                   struct ox820_gmac_dma_request_ctrlblock_t* dmacb)
{
	unsigned long irqflags;

	spin_lock_irqsave(&gmac->dma.tx_free_descriptors_spinlock, irqflags);

	dmacb->last->next = gmac->dma.free_tx_ctrlblocks;
	dmacb->last = NULL;
	gmac->dma.free_tx_ctrlblocks = dmacb;
	gmac->dma.num_free_tx_ctrlblocks += dmacb->dmacb_count;
	wmb();

	spin_unlock_irqrestore(&gmac->dma.tx_free_descriptors_spinlock, irqflags);
}

/*=============================================================================*/
void
ox820_gmac_dma_free_tx_descriptor(struct ox820_gmac_t* gmac,
                                  struct ox820_gmac_dma_request_ctrlblock_t* dmacb)
{
	unsigned long irqflags;

	spin_lock_irqsave(&gmac->dma.tx_free_descriptors_spinlock, irqflags);

	dmacb->next = gmac->dma.free_tx_ctrlblocks;
	dmacb->last = NULL;
	gmac->dma.free_tx_ctrlblocks = dmacb;
	++gmac->dma.num_free_tx_ctrlblocks;
	wmb();

	spin_unlock_irqrestore(&gmac->dma.tx_free_descriptors_spinlock, irqflags);
}

/*=============================================================================*/
enum ox820_gmac_tx_schedule_state_t
ox820_gmac_dma_enqueue_tx_descriptors(struct ox820_gmac_t* gmac,
                                      struct ox820_gmac_dma_request_ctrlblock_t* dmacbs_head)
{
	unsigned long irqflags;
	enum ox820_gmac_tx_schedule_state_t ret = OX820_GMAC_TX_SCHED_NOTEMPTY;

	spin_lock_irqsave(&gmac->dma.tx_schedule_descriptors_spinlock, irqflags);

	if(NULL == gmac->dma.scheduled_tx_ctrlblocks_head) {
		/* empty list so schedule the blocks */
		ret = OX820_GMAC_TX_SCHED_EMPTY;
		gmac->dma.scheduled_tx_ctrlblocks_head = dmacbs_head;
		gmac->dma.scheduled_tx_ctrlblocks_tail = dmacbs_head->last;
	} else {
		/* add another dma cb list to the scheduled list */
		gmac->dma.scheduled_tx_ctrlblocks_tail->next = dmacbs_head;
		gmac->dma.scheduled_tx_ctrlblocks_tail->hw.buffer2 = dmacbs_head->phys_addr;
		gmac->dma.scheduled_tx_ctrlblocks_tail = dmacbs_head->last;
	}
	gmac->dma.scheduled_tx_ctrlblocks_tail->next = NULL;
	wmb();

	spin_unlock_irqrestore(&gmac->dma.tx_schedule_descriptors_spinlock, irqflags);

	return ret;
}

/*=============================================================================*/
void
ox820_gmac_dma_schedule_tx_descriptors(struct ox820_gmac_t* gmac) {
	unsigned long irqflags;

	spin_lock_irqsave(&gmac->dma.tx_schedule_descriptors_spinlock, irqflags);

	if(NULL != gmac->dma.scheduled_tx_ctrlblocks_head && NULL == gmac->dma.active_tx_ctrlblocks_head) {
		gmac->dma.active_tx_ctrlblocks_head = gmac->dma.scheduled_tx_ctrlblocks_head;
		gmac->dma.scheduled_tx_ctrlblocks_head = NULL;
		gmac->dma.scheduled_tx_ctrlblocks_tail = NULL;
		gmac->gmac_regs->dma_tx_descriptor_list = gmac->dma.active_tx_ctrlblocks_head->phys_addr;

		/* trigger DMA on new request block chain */
		ox820_gmac_dma_tx_enable(gmac, 1);
		gmac->gmac_regs->dma_tx_poll_demand = 0;
	}

	spin_unlock_irqrestore(&gmac->dma.tx_schedule_descriptors_spinlock, irqflags);
}

/*=============================================================================*/
void
ox820_gmac_dma_deschedule_tx_descriptors(struct ox820_gmac_t* gmac) {
	struct ox820_gmac_dma_request_ctrlblock_t* prev;
	u32 desc_status;

	while(NULL != gmac->dma.active_tx_ctrlblocks_head) {
		desc_status = gmac->dma.active_tx_ctrlblocks_head->hw.status;
		if(desc_status & MSK_OX820_GMAC_DMA_RX_STATUS_OWN) {
			/* stop here as GMAC is still working on those following */
			break;
		}

		if(0 != gmac->dma.active_tx_ctrlblocks_head->frag_length) {
			dma_unmap_single(0, gmac->dma.active_tx_ctrlblocks_head->hw.buffer1, gmac->dma.active_tx_ctrlblocks_head->frag_length, DMA_TO_DEVICE);
		}

		if(gmac->dma.active_tx_ctrlblocks_head->last == gmac->dma.active_tx_ctrlblocks_head) {
			/* we got the last fragment of a packet */

			struct sk_buff* skb = gmac->dma.active_tx_ctrlblocks_head->skb;

			// Check the status of the transmission
			if (likely(is_tx_valid(desc_status))) {
				gmac->stats.tx_bytes += skb->len;
				gmac->stats.tx_packets++;
			} else {
				gmac->stats.tx_errors++;
				if (is_tx_aborted(desc_status)) {
					++gmac->stats.tx_aborted_errors;
				}
				if (is_tx_carrier_error(desc_status)) {
					++gmac->stats.tx_carrier_errors;
				}
			}

			if (unlikely(is_tx_collision_error(desc_status))) {
				++gmac->stats.collisions;
			}

			// Inform the network stack that packet transmission has finished
			dev_kfree_skb_irq(skb);
		}

		prev = gmac->dma.active_tx_ctrlblocks_head;
		gmac->dma.active_tx_ctrlblocks_head = prev->next;
		ox820_gmac_dma_free_tx_descriptor(gmac, prev);
	}

	if(unlikely(netif_queue_stopped(gmac->netdev)) && gmac->interface_up && gmac->dma.num_free_tx_ctrlblocks >= gmac->dma.allocated_tx_descriptors) {
		/* we had an overflow of frames for the tx descriptors, so after reaching the hysteresis we enable the queuing again */
		netif_wake_queue(gmac->netdev);
	}
}

/*=============================================================================*/
struct sk_buff*
ox820_gmac_dma_rx_desc_attach_skb(struct ox820_gmac_t* gmac,
                                  struct ox820_gmac_dma_request_ctrlblock_t* rx_dmacb)
{
	struct sk_buff* skb;

	/* get a new skb for the rx descriptor */
	skb = dev_alloc_skb(MAX_JUMBO + NET_IP_ALIGN);
	if(NULL != skb) {
		// Despite what the comments in the original code from Synopsys
		// claimed, the GMAC DMA can cope with non-quad aligned buffers
		// - it will always perform quad transfers but zero/ignore the
		// unwanted bytes.
		skb_reserve(skb, NET_IP_ALIGN);

		rx_dmacb->hw.buffer1 = dma_map_single(0, skb->tail, MAX_JUMBO, DMA_FROM_DEVICE);
		rx_dmacb->hw.frag_length = MAX_JUMBO;

		if(dma_mapping_error(0, rx_dmacb->hw.buffer1))
		{
			// Free the socket buffer
			dev_kfree_skb(skb);
			skb = NULL;
		}
	}

	return skb;
}
