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
void ox820_gmac_jumbo_enable(struct ox820_gmac_t* gmac, int enable)
{
	if(enable) {
		gmac->gmac_regs->mac_config |= (MSK_OX820_GMAC_MAC_CONFIG_JE | MSK_OX820_GMAC_MAC_CONFIG_JD | MSK_OX820_GMAC_MAC_CONFIG_WD);
	} else {
		gmac->gmac_regs->mac_config &= ~(MSK_OX820_GMAC_MAC_CONFIG_JE | MSK_OX820_GMAC_MAC_CONFIG_JD | MSK_OX820_GMAC_MAC_CONFIG_WD);
	}
}

/*=============================================================================*/
void ox820_gmac_rxtx_enable(struct ox820_gmac_t* gmac, int enable)
{
	if(enable) {
		gmac->gmac_regs->mac_config |= (MSK_OX820_GMAC_MAC_CONFIG_RE | MSK_OX820_GMAC_MAC_CONFIG_TE);
	} else {
		gmac->gmac_regs->mac_config &= ~(MSK_OX820_GMAC_MAC_CONFIG_RE | MSK_OX820_GMAC_MAC_CONFIG_TE);
	}
}

/*=============================================================================*/
void ox820_gmac_dma_rx_enable(struct ox820_gmac_t* gmac, int enable)
{
	if(enable) {
		gmac->gmac_regs->dma_opmode |= MSK_OX820_GMAC_DMA_OPMODE_SR;
	} else {
		gmac->gmac_regs->dma_opmode &= ~MSK_OX820_GMAC_DMA_OPMODE_SR;
		while((gmac->gmac_regs->dma_status & MSK_OX820_GMAC_DMA_STATUS_RS) != VAL_OX820_GMAC_DMA_STATUS_RS_STOPPED) {
			/* wait for stop */
			yield();
		}
	}
}


/*=============================================================================*/
void ox820_gmac_dma_tx_enable(struct ox820_gmac_t* gmac, int enable)
{
	if(enable) {
		gmac->gmac_regs->dma_opmode |= MSK_OX820_GMAC_DMA_OPMODE_ST;
	} else {
		gmac->gmac_regs->dma_opmode &= ~MSK_OX820_GMAC_DMA_OPMODE_ST;
		while((gmac->gmac_regs->dma_status & MSK_OX820_GMAC_DMA_STATUS_TS) != VAL_OX820_GMAC_DMA_STATUS_TS_STOPPED) {
			/* wait for stop */
			yield();
		}
	}
}

/*=============================================================================*/
void ox820_gmac_config_link_speed(struct ox820_gmac_t* gmac, enum ox820_gmac_linkspeed_t linkspeed, int fullduplex)
{
	unsigned long mac_config = gmac->gmac_regs->mac_config;

	if(gmac->last_configured_linkspeed != linkspeed ||
		gmac->last_configured_fullduplex != fullduplex) {

		switch(linkspeed) {
			case OX820_GMAC_LINKSPEED_10:
				gmac->last_configured_linkspeed = linkspeed;
				mac_config |= MSK_OX820_GMAC_MAC_CONFIG_PS | MSK_OX820_GMAC_MAC_CONFIG_TC;
				mac_config &= (~(MSK_OX820_GMAC_MAC_CONFIG_FES));
				break;

			case OX820_GMAC_LINKSPEED_100:
				gmac->last_configured_linkspeed = linkspeed;
				mac_config |= MSK_OX820_GMAC_MAC_CONFIG_PS | MSK_OX820_GMAC_MAC_CONFIG_FES;
				mac_config &= (~(MSK_OX820_GMAC_MAC_CONFIG_TC));
				break;

			case OX820_GMAC_LINKSPEED_1000:
				gmac->last_configured_linkspeed = linkspeed;
				mac_config &= (~(MSK_OX820_GMAC_MAC_CONFIG_TC | MSK_OX820_GMAC_MAC_CONFIG_PS | MSK_OX820_GMAC_MAC_CONFIG_FES));
				break;

			default:
				break;
		}

		gmac->last_configured_fullduplex = fullduplex;
		if(fullduplex) {
			gmac->gmac_regs->mac_config |= MSK_OX820_GMAC_MAC_CONFIG_DM;
		} else {
			gmac->gmac_regs->mac_config &= (~MSK_OX820_GMAC_MAC_CONFIG_DM);
		}
	}
}

/*=============================================================================*/
int ox820_gmac_set_mac_address(struct net_device *dev, void *p)
{
	struct ox820_gmac_t* gmac = netdev_priv(dev);
	struct sockaddr *addr = p;

	if (!is_valid_ether_addr(addr->sa_data)) {
		return -EADDRNOTAVAIL;
	}

	memcpy(dev->dev_addr, addr->sa_data, dev->addr_len);

	gmac->gmac_regs->mac_addr[0].low = addr->sa_data[0] |
					(addr->sa_data[1] << 8UL) |
					(addr->sa_data[2] << 16UL) |
					(addr->sa_data[3] << 24UL);
	gmac->gmac_regs->mac_addr[0].high = addr->sa_data[4] | (addr->sa_data[5] << 8UL);

	return 0;
}

/*=============================================================================*/
void ox820_gmac_multicast_hash(struct netdev_hw_addr *ha, u32 *hash_lo, u32 *hash_hi)
{
	u32 crc = ether_crc_le(6, ha->addr);
	u32 mask = 1 << ((crc >> 26) & 0x1F);

	if (crc >> 31) {
		*hash_hi |= mask;
	} else {
		*hash_lo |= mask;
	}
}

/*=============================================================================*/
void ox820_gmac_set_multicast_list(struct net_device *dev)
{
	struct ox820_gmac_t* gmac = netdev_priv(dev);
	u32 hash_lo = 0;
	u32 hash_hi = 0;
	u32 mode = 0;
	int i = 0;
	struct netdev_hw_addr *ha;

	// Disable promiscuous mode and uni/multi-cast matching
	gmac->gmac_regs->mac_frame_filter = 0;

	// Disable all perfect match registers
	for (i = 0; i < 16; ++i) {
		if(0 != i) {
			gmac->gmac_regs->mac_addr[i].high = 0;
		}
		gmac->gmac_regs->mac_addr2[i].high = 0;
	}

	// Promiscuous mode overrides all-multi which overrides other filtering
	if (dev->flags & IFF_PROMISC) {
		mode |= MSK_OX820_GMAC_MAC_FRAME_FILTER_PR;
	} else if (dev->flags & IFF_ALLMULTI) {
		mode |= MSK_OX820_GMAC_MAC_FRAME_FILTER_PM;
	} else {

		if (netdev_mc_count(dev) <= 31) {
			// Use perfect matching registers
			netdev_for_each_mc_addr(ha, dev) {
				u32 addr;

				// Note: write to hi register first. The MAC address registers are
				// double-synchronised to the GMII clock domain, and sync is only
				// triggered on the write to the low address register.
				addr  = ha->addr[4];
				addr |= (ha->addr[5] << 8UL);
				addr |= MSK_OX820_GMAC_MAC_ADDR_AE;
				if(i <= 16) {
					gmac->gmac_regs->mac_addr[i - 1].high = addr;
				} else {
					gmac->gmac_regs->mac_addr2[i - 17].high = addr;
				}

				addr  = ha->addr[0];
				addr |= (ha->addr[1] << 8UL);
				addr |= (ha->addr[2] << 16UL);
				addr |= (ha->addr[3] << 24UL);
				if(i <= 16) {
					gmac->gmac_regs->mac_addr[i - 1].low = addr;
				} else {
					gmac->gmac_regs->mac_addr2[i - 17].low = addr;
				}
				i++;
			}
		} else {
			// Use hashing
			mode |= MSK_OX820_GMAC_MAC_FRAME_FILTER_HMC;

			netdev_for_each_mc_addr(ha, dev) {
				ox820_gmac_multicast_hash(ha, &hash_lo, &hash_hi);
			}
		}
	}

	// Update the filtering rules
	gmac->gmac_regs->mac_frame_filter = mode;

	// Update the filtering hash table
	gmac->gmac_regs->hash_table_high = hash_hi;
	gmac->gmac_regs->hash_table_low = hash_lo;
}
