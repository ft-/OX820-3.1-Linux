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
static void ox820_gmac_plain_receive_int(struct ox820_gmac_t* gmac)
{
	struct ox820_gmac_dma_request_ctrlblock_t* prev;
	struct sk_buff* skb;
	u32 desc_status;
	int ip_summed;
	int is_ip;
	int vlan_offset;
	unsigned short eth_protocol;

	while(NULL != gmac->dma.active_rx_ctrlblocks) {
		desc_status = gmac->dma.active_rx_ctrlblocks->hw.status;
		if(desc_status & MSK_OX820_GMAC_DMA_RX_STATUS_OWN) {
			/* stop here as GMAC is still working on those following */
			break;
		}

		prev = gmac->dma.active_rx_ctrlblocks;
		gmac->dma.active_rx_ctrlblocks = prev->next;

		if(likely(0 == (desc_status & (MSK_OX820_GMAC_DMA_RX_STATUS_ES | MSK_OX820_GMAC_DMA_RX_STATUS_IPC))) {
			skb = prev->skb;

			/* unhook skb */
			dma_unmap_single(0, prev->hw.buffer1, prev->hw.frag_length, DMA_FROM_DEVICE);

			// Get the packet data length
			packet_len = get_desc_len(desc_status, last);
			if (packet_len > priv->rx_buffer_size_) {
				DBG(20, KERN_INFO "Received length %d greater than Rx buffer size %d\n", packet_len, priv->rx_buffer_size_);

				// Force a length error into the descriptor status
				desc_status = force_rx_length_error(desc_status);
				goto not_valid_skb;
			}

			ip_summed = CHECKSUM_NONE;

			// Determine whether Ethernet frame contains an IP packet -
			// only bother with Ethernet II frames, but do cope with
			// 802.1Q VLAN tag presence
			vlan_offset = 0;
			eth_protocol = ntohs(((struct ethhdr*)skb->data)->h_proto);
			is_ip = is_ip_packet(eth_protocol);

			if (!is_ip) {
				// Check for VLAN tag
				if (eth_protocol == ETH_P_8021Q) {
					// Extract the contained protocol type from after
					// the VLAN tag
					eth_protocol = ntohs(*(unsigned short*)(skb->data + ETH_HLEN));
					is_ip = is_ip_packet(eth_protocol);

					// Adjustment required to skip the VLAN stuff and
					// get to the IP header
					vlan_offset = 4;
				}
			}

			// Only offload checksum calculation for IP packets
			if (is_ip) {
				struct iphdr* ipv4_header = 0;

				if (unlikely(desc_status & MSK_OX820_GMAC_DMA_RX_STATUS_PCE) {
					valid = 0;
				} else if (is_ipv4_packet(eth_protocol)) {
					ipv4_header = (struct iphdr*)(skb->data + ETH_HLEN + vlan_offset);

					// H/W can only checksum non-fragmented IP packets
					if (!(ipv4_header->frag_off & htons(IP_MF | IP_OFFSET))) {
						if (is_hw_checksummable(ipv4_header->protocol)) {
							ip_summed = CHECKSUM_UNNECESSARY;
						}
					}
				}
#ifdef CONFIG_OXNAS_IPV6_OFFLOAD
				else if (is_ipv6_packet(eth_protocol)) {
					struct ipv6hdr* ipv6_header = (struct ipv6hdr*)(skb->data + ETH_HLEN + vlan_offset);

					if (is_hw_checksummable(ipv6_header->nexthdr)) {
						ip_summed = CHECKSUM_UNNECESSARY;
					}
				}
#endif // CONFIG_OXNAS_IPV6_OFFLOAD
			}

			if (unlikely(!valid)) {
				goto not_valid_skb;
			}

			// Increase the skb's data pointer to account for the RX packet that has
			// been DMAed into it
			skb_put(skb, packet_len);

			// Set the device for the skb
			skb->dev = priv->netdev;

			// Set packet protocol
			skb->protocol = eth_type_trans(skb, priv->netdev);

			// Record whether h/w checksumed the packet
			skb->ip_summed = ip_summed;

			// Send the packet up the network stack
			netif_receive_skb(skb);

			// Update receive statistics
			priv->netdev->last_rx = jiffies;
			++priv->stats.rx_packets;
			priv->stats.rx_bytes += packet_len;


			/* put a new skb to it */
			skb = ox820_gmac_dma_rx_desc_attach_skb(gmac, prev);
		}

		if (unlikely(!skb)) {
			/* no skb, so we go and put that rx dma cb into the incomplete list */
			prev->skb = NULL;
			if(NULL == gmac->dma.incomplete_rx_ctrlblocks_head) {
				gmac->dma.incomplete_rx_ctrlblocks_head = prev;
				gmac->dma.incomplete_rx_ctrlblocks_tail = prev;
				prev->next = NULL;
			} else {
				gmac->dma.incomplete_rx_ctrlblocks_tail->next = prev;
				prev->next = NULL;
				gmac->dma.incomplete_rx_ctrlblocks_tail = prev;
			}
		} else {
			if(NULL == gmac->dma.unused_rx_ctrlblocks_head) {
				gmac->dma.unused_rx_ctrlblocks_head = prev;
				gmac->dma.unused_rx_ctrlblocks_tail = prev;
				prev->next = NULL;
			} else {
				gmac->dma.unused_rx_ctrlblocks_tail->next = prev;
				prev->next = NULL;
				gmac->dma.unused_rx_ctrlblocks_tail = prev;
			}
		}
	}

	if(NULL == gmac->dma.active_rx_ctrlblocks) {
		gmac->dma.active_rx_ctrlblocks = gmac->dma.unused_rx_ctrlblocks_head;
		gmac->dma.unused_rx_ctrlblocks_head = NULL;
		gmac->dma.unused_rx_ctrlblocks_tail = NULL;
		prev = gmac->dma.active_rx_ctrlblocks;
		while(NULL != prev) {
			prev->hw.status |= MSK_OX820_GMAC_DMA_RX_STATUS_OWN;
			prev = prev->next;
		}
		ox820_gmac_dma_rx_enable(gmac, 1);
		gmac->gmac_regs->dma_rx_poll_demand = 0;
	}
}

/*=============================================================================*/
static void ox820_gmac_plain_set_rx_packet_info(struct net_device* dev)
{

}

/*=============================================================================*/
int ox820_gmac_plain_open(struct net_device* dev) {
	struct ox820_gmac_t* gmac = (struct ox820_gmac_t*)netdev_priv(dev);
	int ret;

	/* disallow MDIO accesses through the specified gmac */
	ret = ox820_gmac_mdio_lock(gmac->gmac_unit);
	if(0 != ret) {
		return ret;
	}

	ox820_gmac_initialize_regs(gmac);

	/* allow MDIO accesses through the specified gmac */
	ox820_gmac_mdio_unlock(gmac->gmac_unit);

	// Set length etc. of rx packets
	ox820_gmac_plain_set_rx_packet_info(dev);

	// Setup Jumbo frame support
	ox820_gmac_jumbo_enable(gmac, dev->mtu > NORMAL_PACKET_SIZE);

	ox820_gmac_rxtx_enable(gmac, 1);

	gmac->interface_up = 1;

	netif_start_queue(dev);
	return 0;
}

/*=============================================================================*/
int ox820_gmac_plain_stop(struct net_device* dev) {
	struct ox820_gmac_t* gmac = (struct ox820_gmac_t*)netdev_priv(dev);
	int ret = 0;

	gmac->interface_up = 0;
	netif_stop_queue(dev);
	netif_carrier_off(dev);

	ox820_gmac_rxtx_enable(gmac, 0);

	return ret;
}

/*=============================================================================*/
int ox820_gmac_plain_change_mtu(struct net_device *dev, int new_mtu)
{
	int status = 0;
	struct ox820_gmac_t* gmac = (struct ox820_gmac_t*)netdev_priv(dev);
	int original_mtu = dev->mtu;

	printk(KERN_INFO "Attempting to set new mtu %d\n", new_mtu);

	// Check that new MTU is within supported range
	if ((new_mtu < MIN_PACKET_SIZE) || (new_mtu > MAX_JUMBO)) {
		printk(KERN_WARNING "ox820_gmac_change_mtu() %s: Invalid MTU %d\n", dev->name, new_mtu);
		status = -EINVAL;
	} else if (gmac->interface_up) {

		// Record the new MTU, so bringing the MAC back up will allocate
		// resources to suit the new MTU
		dev->mtu = new_mtu;

		// Disable Receive on DMA
		ox820_gmac_dma_rx_enable(gmac, 0);

		// Set length etc. of rx packets
		ox820_gmac_plain_set_rx_packet_info(dev);

		// Enable Receive on DMA
		ox820_gmac_dma_rx_enable(gmac, 0);

		// Setup Jumbo frame support
		ox820_gmac_jumbo_enable(gmac, dev->mtu > NORMAL_PACKET_SIZE);

	} else {
		// Record the new MTU, so bringing the interface up will allocate
		// resources to suit the new MTU
		dev->mtu = new_mtu;
	}

	// If there was a failure
	if (status) {
		// Return the MTU to its original value
		printk(KERN_INFO "change_mtu() Failed, returning MTU to original value\n");
		dev->mtu = original_mtu;
	}

	return status;
}

/*=============================================================================*/
static inline void ox820_gmac_unmap_fragments(
    tx_frag_info_t *frags,
    int             count)
{
	while (count--) {
		dma_unmap_single(0, frags->phys_adr, frags->length, DMA_TO_DEVICE);
		++frags;
	}
}

/*=============================================================================*/
static inline int ox820_gmac_num_descriptors_needed(u16 length)
{
	int count = length >> OX820_GMAC_MAX_DESCRIPTOR_SHIFT;
	if (length & OX820_GMAC_MAX_DESCRIPTOR_LENGTH) {
		++count;
	}
	return count;
}

/*=============================================================================*/
static enum ox820_gmac_tx_schedule_state_t ox820_gmac_set_tx_descriptor(
								struct ox820_gmac_t *gmac,
								struct sk_buff *skb,
								tx_frag_info_t *frag_info,
								int             frag_count,
								int             use_hw_csum)
{
	int num_descriptors = frag_count;
	int frag_index = 0;
	int check_oversized_frags = gmac->netdev->mtu >= (OX820_GMAC_MAX_DESCRIPTOR_LENGTH - ETH_HLEN);
	struct ox820_gmac_dma_request_ctrlblock_t* dmacbs_head;
	struct ox820_gmac_dma_request_ctrlblock_t* descriptor;

	if (unlikely(check_oversized_frags)) {
		// Calculate the number of extra descriptors required due to fragments
		// being longer than the maximum buffer size that can be described by a
		// single descriptor
		num_descriptors = 0;
		do {
			// How many descriptors are required to describe the fragment?
			num_descriptors += ox820_gmac_num_descriptors_needed(frag_info[frag_index].length);
		} while (++frag_index < frag_count);
	}


	// Are sufficient descriptors available for writing by the CPU?
	dmacbs_head = ox820_gmac_dma_alloc_tx_descriptors(gmac, num_descriptors);
	if(NULL == dmacbs_head) {
		return OX820_GMAC_TX_SCHED_BUSY;
	}

	descriptor = dmacbs_head;
	descriptor->last->skb = skb;
	frag_index = 0;
	do {
		u16        part_length = frag_info[frag_index].length;
		dma_addr_t phys_adr    = frag_info[frag_index].phys_adr;
		int        part        = 0;
		int        parts       = 1;

		if (unlikely(check_oversized_frags)) {
			// How many descriptors are required to describe the fragment?
			parts = ox820_gmac_num_descriptors_needed(part_length);
		}

		descriptor->frag_length = part_length;

		// Setup a descriptor for each part of the fragment that can be
		// described by a single descriptor
		do {
			int                       last_part  = (part == (parts - 1));
			u32                       length     = 0;
			u32                       status     = 0;

			// no second buffer but TCH is already cleared */

			// Set the Tx checksum mode
			if (use_hw_csum) {
				status |= VAL_OX820_GMAC_DMA_TX_STATUS_CIC_FULL;
			}

			// Set fragment buffer length
			length |= ((part_length > OX820_GMAC_MAX_DESCRIPTOR_LENGTH ? OX820_GMAC_MAX_DESCRIPTOR_LENGTH : part_length) << BIT_OX820_GMAC_DMA_TX_LENGTH_TBS1);

			// Set fragment buffer address
			descriptor->hw.buffer1 = phys_adr;

			// Is this descriptor not the last describing a single fragment
			// buffer?
			if (!last_part) {
				// Update the fragment buffer part details
				part_length -= OX820_GMAC_MAX_DESCRIPTOR_LENGTH;
				phys_adr    += OX820_GMAC_MAX_DESCRIPTOR_LENGTH;
			}

			/* we can change ownership right now since we have not yet scheduled the fragments */
			status |= MSK_OX820_GMAC_DMA_TX_STATUS_OWN;
			// Write the assembled status descriptor entry to the descriptor
			descriptor->hw.status |= status;

			// Write the assembled length descriptor entry to the descriptor
			descriptor->hw.length = length;

			if(0 != part) {
				descriptor->frag_length = 0;
			}

			/* advance to next descriptor */
			descriptor = descriptor->next;
		} while (++part < parts);
	} while (++frag_index < frag_count);

	// Ensure all prior writes to the descriptors shared with MAC have
	// completed before setting the descriptor ownership flags to transfer
	// ownership to the GMAC
	wmb();

	// Schedule descriptors
	return ox820_gmac_dma_enqueue_tx_descriptors(gmac, dmacbs_head);
}

/*=============================================================================*/
static int ox820_gmac_plain_start_xmit(
    struct sk_buff    *skb,
    struct net_device *dev)
{
	enum ox820_gmac_tx_schedule_state_t tx_sched_ret;
	struct ox820_gmac_t    *gmac = (struct ox820_gmac_t*)netdev_priv(dev);
	struct skb_shared_info *shinfo = skb_shinfo(skb);
	int                     fragment_count = shinfo->nr_frags + 1;
	tx_frag_info_t          fragments[fragment_count];
	int                     frag_index;

	if (shinfo->frag_list) {
		int err;

		printk(KERN_WARNING "Linearizing skb with frag_list\n");
		err = skb_linearize(skb);
		if (err) {
			panic("hard_start_xmit() Failed to linearize skb with frag_list\n");
		}
	}

	// Map the main buffer
	fragments[0].length = skb_headlen(skb);
	fragments[0].phys_adr = dma_map_single(0, skb->data, skb_headlen(skb), DMA_TO_DEVICE);
	BUG_ON(dma_mapping_error(0, fragments[0].phys_adr));

	// Map any SG fragments
	for (frag_index = 0; frag_index < shinfo->nr_frags; ++frag_index) {
		skb_frag_t *frag = &shinfo->frags[frag_index];

		fragments[frag_index + 1].phys_adr = dma_map_page(0, frag->page, frag->page_offset, frag->size, DMA_TO_DEVICE);
		BUG_ON(dma_mapping_error(0, fragments[frag_index + 1].phys_adr));

		fragments[frag_index + 1].length = frag->size;
	}

	// Construct the GMAC DMA descriptor
	tx_sched_ret = ox820_gmac_set_tx_descriptor(gmac, skb, fragments, fragment_count, skb->ip_summed == CHECKSUM_PARTIAL);

	switch(tx_sched_ret) {
		case OX820_GMAC_TX_SCHED_BUSY:
			// Stop further calls to hard_start_xmit() until some descriptors are
			// freed up by already queued TX packets being completed
			netif_stop_queue(dev);
			return NETDEV_TX_BUSY;

		case OX820_GMAC_TX_SCHED_NOTEMPTY:
			break;

		case OX820_GMAC_TX_SCHED_EMPTY:
			/* trigger scheduling */
			ox820_gmac_dma_schedule_tx_descriptors(gmac);
			break;
	}

	return NETDEV_TX_OK;
}

/*=============================================================================*/
const struct net_device_ops ox820_gmac_plain_netdev_ops = {
	.ndo_open			= ox820_gmac_plain_open,
	.ndo_stop			= ox820_gmac_plain_stop,
	.ndo_start_xmit			= ox820_gmac_plain_start_xmit,
	.ndo_get_stats			= ox820_gmac_get_stats,
	.ndo_set_multicast_list		= ox820_gmac_set_multicast_list,
	.ndo_set_mac_address		= ox820_gmac_set_mac_address,
	.ndo_change_mtu			= ox820_gmac_plain_change_mtu,
#ifdef CONFIG_NET_POLL_CONTROLLER
	.ndo_poll_controller		= ox820_gmac_netpoll,
#endif
};

/*=============================================================================*/
int ox820_gmac_plain_init(struct net_device* netdev, struct ox820_gmac_t* gmac)
{
	gmac->gmac_tx_int = ox820_gmac_dma_deschedule_tx_descriptors;
	gmac->gmac_rx_int = ox820_gmac_plain_receive_int;

	netdev->netdev_ops = &ox820_gmac_plain_netdev_ops;

	return 0;
}
