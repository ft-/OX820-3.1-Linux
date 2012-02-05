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
#ifndef _ox820_gmac_h
#define _ox820_gmac_h

#include <linux/types.h>
#include <mach/hw/gmac.h>
#include <mach/hw/sysctrl.h>
#include <mach/hardware.h>
#include <mach/leon.h>
#include <linux/irq.h>
#include <linux/netdevice.h>
#include <linux/interrupt.h>
#include <linux/sched.h>
#include <linux/mii.h>
#include <linux/skbuff.h>
#include <linux/semaphore.h>
#include <linux/printk.h>
#include <linux/etherdevice.h>
#include <linux/crc32.h>

static const int MIN_PACKET_SIZE = 68;
static const int MAX_JUMBO = (8*1024);
static const int NORMAL_PACKET_SIZE = 1500;

enum ox820_gmac_linkspeed_t
{
	OX820_GMAC_LINKSPEED_UNDEF = 0,
	OX820_GMAC_LINKSPEED_10 = 10,
	OX820_GMAC_LINKSPEED_100 = 100,
	OX820_GMAC_LINKSPEED_1000 = 1000,
};

/* DMA request control block */
struct ox820_gmac_dma_request_ctrlblock_t
{
	struct ox820_gmac_dma_desc_t			hw;
	struct ox820_gmac_dma_request_ctrlblock_t* 	next;
	struct ox820_gmac_dma_request_ctrlblock_t* 	prev;	/* not used in free list */
	struct ox820_gmac_dma_request_ctrlblock_t* 	last;	/* only used for marking the end of a frame */
	struct ox820_gmac_dma_request_ctrlblock_t* 	head;	/* only used for marking the beginning of a frame */
	dma_addr_t					phys_addr;
	struct sk_buff*					skb;
	u32						dmacb_count;
	u32						frag_length;	/* 0 if no release on this one */
};

struct ox820_gmac_t
{
	u32				gmac_unit;
	struct ox820_gmac_registers_t*	gmac_regs;
	struct ox820_netoe_registers_t*	netoe_regs;
	enum ox820_gmac_linkspeed_t	last_configured_linkspeed;
	int				last_configured_fullduplex;

	struct net_device*		netdev;
	struct device* 			dev;

	struct net_device_stats		stats;

	/** PHY related info */
	struct mii_if_info		mii;
	struct ethtool_cmd		ethtool_cmd;
	struct ethtool_pauseparam	ethtool_pauseparam;

	int				interface_up;

	void (*                         gmac_rx_int)(struct ox820_gmac_t*);

	void (*                         gmac_tx_int)(struct ox820_gmac_t*);

	struct {
		struct ox820_gmac_dma_request_ctrlblock_t*
						free_tx_ctrlblocks;
		u32				num_free_tx_ctrlblocks;
		struct ox820_gmac_dma_request_ctrlblock_t*
						scheduled_tx_ctrlblocks_head;
		struct ox820_gmac_dma_request_ctrlblock_t*
						scheduled_tx_ctrlblocks_tail;
		struct ox820_gmac_dma_request_ctrlblock_t*
						active_tx_ctrlblocks_head;

		struct ox820_gmac_dma_request_ctrlblock_t*
						unused_rx_ctrlblocks_head;
		struct ox820_gmac_dma_request_ctrlblock_t*
						unused_rx_ctrlblocks_tail;
		struct ox820_gmac_dma_request_ctrlblock_t*
						incomplete_rx_ctrlblocks_head;
		struct ox820_gmac_dma_request_ctrlblock_t*
						incomplete_rx_ctrlblocks_tail;
		struct ox820_gmac_dma_request_ctrlblock_t*
						active_rx_ctrlblocks;

		dma_addr_t			rx_descriptors_pa;
		dma_addr_t			tx_descriptors_pa;
		struct ox820_gmac_dma_request_ctrlblock_t*
						rx_descriptors_va;
		struct ox820_gmac_dma_request_ctrlblock_t*
						tx_descriptors_va;

		spinlock_t			tx_free_descriptors_spinlock;
		spinlock_t			tx_schedule_descriptors_spinlock;
		unsigned int			allocated_tx_descriptors;
		unsigned int			allocated_rx_descriptors;
	} dma;
};

/*=============================================================================*/
/* ox820_gmac_init.c */
void ox820_gmac_initialize_regs(struct ox820_gmac_t* gmac);

/*=============================================================================*/
/* ox820_gmac_config.c */
void ox820_gmac_config_link_speed(struct ox820_gmac_t* gmac, enum ox820_gmac_linkspeed_t linkspeed, int fdx);

int ox820_gmac_set_mac_address(struct net_device *dev, void *p);

void ox820_gmac_set_multicast_list(struct net_device *dev);

void ox820_gmac_jumbo_enable(struct ox820_gmac_t* gmac, int enable);

void ox820_gmac_rxtx_enable(struct ox820_gmac_t* gmac, int enable);

void ox820_gmac_dma_rx_enable(struct ox820_gmac_t* gmac, int enable);

void ox820_gmac_dma_tx_enable(struct ox820_gmac_t* gmac, int enable);

/*=============================================================================*/
/* ox820_gmac_common.c */
struct net_device_stats *ox820_gmac_get_stats(struct net_device *dev);

#ifdef CONFIG_NET_POLL_CONTROLLER
void ox820_gmac_netpoll(struct net_device *netdev);
#endif

/*=============================================================================*/
/* ox820_gmac_plain.c */
int ox820_gmac_plain_open(struct net_device* netdev);

int ox820_gmac_plain_stop(struct net_device* netdev);

int ox820_gmac_plain_change_mtu(struct net_device *dev, int new_mtu);

extern const struct net_device_ops ox820_gmac_plain_netdev_ops;

/*=============================================================================*/
/* ox820_gmac_phy.c */
int ox820_gmac_mdio_read(u32 gmac_unit,
                         u32 phyaddr,
                         u32 phyreg,
                         u16* phyval);

int ox820_gmac_mdio_write(u32 gmac_unit,
                          u32 phyaddr,
                          u32 phyreg,
                          u16 phyval);

int ox820_gmac_mdio_lock(u32 gmac_unit);

int ox820_gmac_mdio_unlock(u32 gmac_unit);

/*=============================================================================*/
/* ox820_gmac_dma.c */
int ox820_gmac_dma_init(struct ox820_gmac_t* gmac,
                        unsigned int num_rx_descriptors,
                        unsigned int num_tx_descriptors);

int ox820_gmac_dma_cleanup(struct ox820_gmac_t* gmac);

struct ox820_gmac_dma_request_ctrlblock_t*
ox820_gmac_dma_alloc_tx_descriptors(struct ox820_gmac_t* gmac,
                                    unsigned int num_descriptors);

void
ox820_gmac_dma_free_tx_descriptors(struct ox820_gmac_t* gmac,
                                   struct ox820_gmac_dma_request_ctrlblock_t* dmacbs_head);

void
ox820_gmac_dma_free_tx_descriptor(struct ox820_gmac_t* gmac,
                                  struct ox820_gmac_dma_request_ctrlblock_t* dmacbs_single);

struct sk_buff*
ox820_gmac_dma_rx_desc_attach_skb(struct ox820_gmac_t* gmac,
                                  struct ox820_gmac_dma_request_ctrlblock_t* rx_dmacb);

enum ox820_gmac_tx_schedule_state_t
{
	OX820_GMAC_TX_SCHED_NOTEMPTY,
	OX820_GMAC_TX_SCHED_EMPTY,
	OX820_GMAC_TX_SCHED_BUSY,
};
enum ox820_gmac_tx_schedule_state_t
ox820_gmac_dma_enqueue_tx_descriptors(struct ox820_gmac_t* gmac,
                                      struct ox820_gmac_dma_request_ctrlblock_t* dmacbs_head);

void
ox820_gmac_dma_schedule_tx_descriptors(struct ox820_gmac_t* gmac);

void
ox820_gmac_dma_deschedule_tx_descriptors(struct ox820_gmac_t* gmac);

typedef struct tx_frag_info {
    dma_addr_t  phys_adr;
    u16         length;
} tx_frag_info_t;

/*=============================================================================*/

#define OX820_MS_TO_JIFFIES(x) (((x) < (1000/(HZ))) ? 1 : (x) * (HZ) / 1000)

#endif
