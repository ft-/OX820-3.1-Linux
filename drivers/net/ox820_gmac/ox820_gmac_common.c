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
struct net_device_stats *ox820_gmac_get_stats(struct net_device *dev)
{
    struct ox820_gmac_t* gmac = (struct ox820_gmac_t*)netdev_priv(dev);
    return &gmac->stats;
}

/*=============================================================================*/
#ifdef CONFIG_NET_POLL_CONTROLLER
/**
 * Polling 'interrupt' - used by things like netconsole to send skbs without
 * having to re-enable interrupts. It's not called while the interrupt routine
 * is executing.
 */
void ox820_gmac_netpoll(struct net_device *netdev)
{
    disable_irq(netdev->irq);
    int_handler(netdev->irq, netdev); // only 2 arguments.
    enable_irq(netdev->irq);
}
#endif // CONFIG_NET_POLL_CONTROLLER
