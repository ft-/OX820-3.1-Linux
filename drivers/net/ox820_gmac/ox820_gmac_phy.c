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

static const int PHY_TRANSFER_TIMEOUT_MS = 100;

static DEFINE_SEMAPHORE(ox820_gmac0_phy_semaphore);
static DEFINE_SEMAPHORE(ox820_gmac1_phy_semaphore);

static struct semaphore* ox820_gmac_phy_semaphores[2] = {
 	 &ox820_gmac0_phy_semaphore,
 	 &ox820_gmac1_phy_semaphore
};

/*=============================================================================*/
int ox820_gmac_mdio_lock(u32 gmac_unit)
{
	switch(gmac_unit) {
		case 0:
		case 1:
			break;
		default:
			return -EINVAL;
	}

	while(down_interruptible(ox820_gmac_phy_semaphores[gmac_unit]));
	return 0;
}

/*=============================================================================*/
int ox820_gmac_mdio_unlock(u32 gmac_unit)
{
	switch(gmac_unit) {
		case 0:
		case 1:
			break;
		default:
			return -EINVAL;
	}

	up(ox820_gmac_phy_semaphores[gmac_unit]);
	return 0;
}

/*=============================================================================*/
int ox820_gmac_mdio_read(u32 gmac_unit,
                         u32 phyaddr,
                         u32 phyreg,
                         u16* phyval)
{
	int ret;
	u32 gmii_addr;
	unsigned long end;
	struct ox820_gmac_registers_t* gmac_regs;

	if(phyaddr > 31 || phyreg > 31) {
		return -EINVAL;
	}

	switch(gmac_unit) {
		case 0:
			gmac_regs = (struct ox820_gmac_registers_t*) ETHA_BASE;
			break;
		case 1:
			gmac_regs = (struct ox820_gmac_registers_t*) ETHB_BASE;
			break;
		default:
			return -EINVAL;
	}

	while(down_interruptible(ox820_gmac_phy_semaphores[gmac_unit]));

	gmii_addr = (phyaddr << BIT_OX820_GMAC_GMII_ADDR_PA) |
		(phyreg << BIT_OX820_GMAC_GMII_ADDR_GR) |
		(5 << BIT_OX820_GMAC_GMII_ADDR_CR);

	if(gmac_regs->gmii_address & MSK_OX820_GMAC_GMII_ADDR_GB) {
		ret = -EBUSY;
	} else {
		gmac_regs->gmii_address = gmii_addr;
		end = jiffies + OX820_MS_TO_JIFFIES(PHY_TRANSFER_TIMEOUT_MS);
		ret = -EIO;
		while (time_before(jiffies, end)) {
			yield();
			if(!(gmac_regs->gmii_address & MSK_OX820_GMAC_GMII_ADDR_GB)) {
				*phyval = gmac_regs->gmii_data;
				ret = 0;
				break;
			}
		}
	}

	up(ox820_gmac_phy_semaphores[gmac_unit]);

	return ret;
}

/*=============================================================================*/
int ox820_gmac_mdio_write(u32 gmac_unit,
                          u32 phyaddr,
                          u32 phyreg,
                          u16 phyval)
{
	int ret;
	u32 gmii_addr;
	unsigned long end;
	struct ox820_gmac_registers_t* gmac_regs;

	if(phyaddr > 31 || phyreg > 31) {
		return -EINVAL;
	}

	switch(gmac_unit) {
		case 0:
			gmac_regs = (struct ox820_gmac_registers_t*) ETHA_BASE;
			break;
		case 1:
			gmac_regs = (struct ox820_gmac_registers_t*) ETHB_BASE;
			break;
		default:
			return -EINVAL;
	}

	while(down_interruptible(ox820_gmac_phy_semaphores[gmac_unit]));

	gmii_addr = (phyaddr << BIT_OX820_GMAC_GMII_ADDR_PA) |
		(phyreg << BIT_OX820_GMAC_GMII_ADDR_GR) |
		(5 << BIT_OX820_GMAC_GMII_ADDR_CR) |
		MSK_OX820_GMAC_GMII_ADDR_GW;

	if(gmac_regs->gmii_address & MSK_OX820_GMAC_GMII_ADDR_GB) {
		ret = -EBUSY;
	} else {
		gmac_regs->gmii_address = gmii_addr;
		gmac_regs->gmii_data = phyval;

		end = jiffies + OX820_MS_TO_JIFFIES(PHY_TRANSFER_TIMEOUT_MS);
		ret = -EIO;
		while (time_before(jiffies, end)) {
			yield();
			if(!(gmac_regs->gmii_address & MSK_OX820_GMAC_GMII_ADDR_GB)) {
				ret = 0;
				break;
			}
		}
	}

	up(ox820_gmac_phy_semaphores[gmac_unit]);

	return ret;
}
