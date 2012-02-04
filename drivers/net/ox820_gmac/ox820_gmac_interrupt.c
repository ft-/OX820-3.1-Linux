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
irqreturn_t ox820_gmac_irq_handler(int irq, struct irq_desc* irqdesc)
{
	struct ox820_gmac_t* gmac = irq_get_handler_data(irq);
	u32 dma_status = gmac->gmac_regs->dma_status;
	gmac->gmac_regs->dma_status = dma_status;

	if(dma_status & MSK_OX820_GMAC_DMA_STATUS_GLI) {
		/* RGMII/SMII Link Status */
		u32 mii_status = gmac->gmac_regs->mii_status;
		/* reconfigure link when it is up */
		if(mii_status & MSK_OX820_GMAC_MII_STATUS_LINK_UP) {
			switch(mii_status & MSK_OX820_GMAC_MII_STATUS_LINK_SPEED) {
				case VAL_OX820_GMAC_MII_STATUS_LINK_SPEED_2_5MHZ:
					ox820_gmac_config_link_speed(gmac,
					                             OX820_GMAC_LINKSPEED_10,
					                             0 != (mii_status & MSK_OX820_GMAC_MII_STATUS_LINK_MODE));
					break;
				case VAL_OX820_GMAC_MII_STATUS_LINK_SPEED_25MHZ:
					ox820_gmac_config_link_speed(gmac,
					                             OX820_GMAC_LINKSPEED_100,
					                             0 != (mii_status & MSK_OX820_GMAC_MII_STATUS_LINK_MODE));
					break;
				case VAL_OX820_GMAC_MII_STATUS_LINK_SPEED_125MHZ:
					ox820_gmac_config_link_speed(gmac,
					                             OX820_GMAC_LINKSPEED_1000,
					                             0 != (mii_status & MSK_OX820_GMAC_MII_STATUS_LINK_MODE));
					break;
			}
		}
	}

	if(dma_status & MSK_OX820_GMAC_DMA_STATUS_RI) {
		/* handle receive */
		gmac->gmac_rx_int(gmac);
	}

	if(dma_status & (MSK_OX820_GMAC_DMA_STATUS_TI | MSK_OX820_GMAC_DMA_STATUS_ETI | MSK_OX820_GMAC_DMA_STATUS_TJT | MSK_OX820_GMAC_DMA_STATUS_UNF)) {
		/* handle transmit */
		gmac->gmac_tx_int(gmac);
	}

	return IRQ_HANDLED;
}
