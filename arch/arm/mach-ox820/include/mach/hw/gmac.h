/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _ox820_hw_gmac_h
#define _ox820_hw_gmac_h

#include <linux/types.h>

/* DMA descriptor block */
struct ox820_gmac_dma_desc_t {
    /** The encoded status field of the GMAC descriptor */
    u32 status;
    /** The encoded length field of GMAC descriptor */
    u32 length;
    /** Buffer 1 pointer field of GMAC descriptor */
    u32 buffer1;
    /** Buffer 2 pointer or next descriptor pointer field of GMAC descriptor */
    u32 buffer2;
};

/* status (rx_desc) */
#define MSK_OX820_GMAC_DMA_RX_STATUS_OWN	0x80000000
#define BIT_OX820_GMAC_DMA_RX_STATUS_OWN	31
#define MSK_OX820_GMAC_DMA_RX_STATUS_AFM	0x40000000
#define BIT_OX820_GMAC_DMA_RX_STATUS_AFM	30
#define MSK_OX820_GMAC_DMA_RX_STATUS_FL		0x3FFF0000
#define BIT_OX820_GMAC_DMA_RX_STATUS_FL		16
#define MSK_OX820_GMAC_DMA_RX_STATUS_ES		0x00008000
#define BIT_OX820_GMAC_DMA_RX_STATUS_ES		15
#define MSK_OX820_GMAC_DMA_RX_STATUS_DE		0x00004000
#define BIT_OX820_GMAC_DMA_RX_STATUS_DE		14
#define MSK_OX820_GMAC_DMA_RX_STATUS_SAF	0x00002000
#define BIT_OX820_GMAC_DMA_RX_STATUS_SAF	13
#define MSK_OX820_GMAC_DMA_RX_STATUS_LE		0x00001000
#define BIT_OX820_GMAC_DMA_RX_STATUS_LE		12
#define MSK_OX820_GMAC_DMA_RX_STATUS_OE		0x00000800
#define BIT_OX820_GMAC_DMA_RX_STATUS_OE		11
#define MSK_OX820_GMAC_DMA_RX_STATUS_VLAN	0x00000400
#define BIT_OX820_GMAC_DMA_RX_STATUS_VLAN	10
#define MSK_OX820_GMAC_DMA_RX_STATUS_FS		0x00000200
#define BIT_OX820_GMAC_DMA_RX_STATUS_FS		9
#define MSK_OX820_GMAC_DMA_RX_STATUS_LS		0x00000100
#define BIT_OX820_GMAC_DMA_RX_STATUS_LS		8
#define MSK_OX820_GMAC_DMA_RX_STATUS_IPC	0x00000080
#define BIT_OX820_GMAC_DMA_RX_STATUS_IPC	7
#define MSK_OX820_GMAC_DMA_RX_STATUS_LC		0x00000040
#define BIT_OX820_GMAC_DMA_RX_STATUS_LC		6
#define MSK_OX820_GMAC_DMA_RX_STATUS_FT		0x00000020
#define BIT_OX820_GMAC_DMA_RX_STATUS_FT		5
#define MSK_OX820_GMAC_DMA_RX_STATUS_RWT	0x00000010
#define BIT_OX820_GMAC_DMA_RX_STATUS_RWT	4
#define MSK_OX820_GMAC_DMA_RX_STATUS_RE		0x00000008
#define BIT_OX820_GMAC_DMA_RX_STATUS_RE		3
#define MSK_OX820_GMAC_DMA_RX_STATUS_DRE	0x00000004
#define BIT_OX820_GMAC_DMA_RX_STATUS_DRE	2
#define MSK_OX820_GMAC_DMA_RX_STATUS_CE		0x00000002
#define BIT_OX820_GMAC_DMA_RX_STATUS_CE		1
#define MSK_OX820_GMAC_DMA_RX_STATUS_PCE	0x00000001
#define BIT_OX820_GMAC_DMA_RX_STATUS_PCE	0

/* status (tx_desc0) */
#define MSK_OX820_GMAC_DMA_TX_STATUS_OWN	0x80000000
#define BIT_OX820_GMAC_DMA_TX_STATUS_OWN	31
#define MSK_OX820_GMAC_DMA_TX_STATUS_IC		0x40000000
#define BIT_OX820_GMAC_DMA_TX_STATUS_IC		30
#define MSK_OX820_GMAC_DMA_TX_STATUS_LS		0x20000000
#define BIT_OX820_GMAC_DMA_TX_STATUS_LS		29
#define MSK_OX820_GMAC_DMA_TX_STATUS_FS		0x10000000
#define BIT_OX820_GMAC_DMA_TX_STATUS_FS		28
#define MSK_OX820_GMAC_DMA_TX_STATUS_DC		0x08000000
#define BIT_OX820_GMAC_DMA_TX_STATUS_DC		27
#define MSK_OX820_GMAC_DMA_TX_STATUS_DP		0x08000000
#define BIT_OX820_GMAC_DMA_TX_STATUS_DP		27
#define MSK_OX820_GMAC_DMA_TX_STATUS_CIC	0x00C00000
#define BIT_OX820_GMAC_DMA_TX_STATUS_CIC	22
#define VAL_OX820_GMAC_DMA_TX_STATUS_CIC_NONE	0x00000000
#define VAL_OX820_GMAC_DMA_TX_STATUS_CIC_HDR	0x00400000
#define VAL_OX820_GMAC_DMA_TX_STATUS_CIC_PAYLD	0x00800000
#define VAL_OX820_GMAC_DMA_TX_STATUS_CIC_FULL	0x00C00000
#define MSK_OX820_GMAC_DMA_TX_STATUS_TER	0x00200000
#define BIT_OX820_GMAC_DMA_TX_STATUS_TER	21
#define MSK_OX820_GMAC_DMA_TX_STATUS_TCH	0x00100000
#define BIT_OX820_GMAC_DMA_TX_STATUS_TCH	20
#define MSK_OX820_GMAC_DMA_TX_STATUS_IHE	0x00010000
#define BIT_OX820_GMAC_DMA_TX_STATUS_IHE	16
#define MSK_OX820_GMAC_DMA_TX_STATUS_ES		0x00008000
#define BIT_OX820_GMAC_DMA_TX_STATUS_ES		15
#define MSK_OX820_GMAC_DMA_TX_STATUS_JT		0x00004000
#define BIT_OX820_GMAC_DMA_TX_STATUS_JT		14
#define MSK_OX820_GMAC_DMA_TX_STATUS_FF		0x00002000
#define BIT_OX820_GMAC_DMA_TX_STATUS_FF		13
#define MSK_OX820_GMAC_DMA_TX_STATUS_IPE	0x00001000
#define BIT_OX820_GMAC_DMA_TX_STATUS_IPE	12
#define MSK_OX820_GMAC_DMA_TX_STATUS_LOC	0x00000800
#define BIT_OX820_GMAC_DMA_TX_STATUS_LOC	11
#define MSK_OX820_GMAC_DMA_TX_STATUS_NC		0x00000400
#define BIT_OX820_GMAC_DMA_TX_STATUS_NC		10
#define MSK_OX820_GMAC_DMA_TX_STATUS_LC		0x00000200
#define BIT_OX820_GMAC_DMA_TX_STATUS_LC		9
#define MSK_OX820_GMAC_DMA_TX_STATUS_EC		0x00000100
#define BIT_OX820_GMAC_DMA_TX_STATUS_EC		8
#define MSK_OX820_GMAC_DMA_TX_STATUS_VF		0x00000080
#define BIT_OX820_GMAC_DMA_TX_STATUS_VF		7
#define MSK_OX820_GMAC_DMA_TX_STATUS_CC		0x00000078
#define BIT_OX820_GMAC_DMA_TX_STATUS_CC		3
#define MSK_OX820_GMAC_DMA_TX_STATUS_ED		0x00000004
#define BIT_OX820_GMAC_DMA_TX_STATUS_ED		2
#define MSK_OX820_GMAC_DMA_TX_STATUS_UF		0x00000002
#define BIT_OX820_GMAC_DMA_TX_STATUS_UF		1
#define MSK_OX820_GMAC_DMA_TX_STATUS_DB		0x00000001
#define BIT_OX820_GMAC_DMA_TX_STATUS_DB		0

/* length (tx_desc1) */
#define MSK_OX820_GMAC_DMA_TX_LENGTH_TBS2	0x1FFF0000
#define BIT_OX820_GMAC_DMA_TX_LENGTH_TBS2	16
#define MSK_OX820_GMAC_DMA_TX_LENGTH_TBS1	0x00001FFF
#define BIT_OX820_GMAC_DMA_TX_LENGTH_TBS1	0


static inline int is_tx_valid(u32 status)
{
    return !(status & MSK_OX820_GMAC_DMA_TX_STATUS_ES);
}

static inline int is_tx_collision_error(u32 status)
{
    return (status & MSK_OX820_GMAC_DMA_TX_STATUS_CC) >> BIT_OX820_GMAC_DMA_TX_STATUS_CC;
}

static inline int is_tx_aborted(u32 status)
{
    return status & (MSK_OX820_GMAC_DMA_TX_STATUS_LC | MSK_OX820_GMAC_DMA_TX_STATUS_EC);
}

static inline int is_tx_carrier_error(u32 status)
{
    return status & (MSK_OX820_GMAC_DMA_TX_STATUS_LOC | MSK_OX820_GMAC_DMA_TX_STATUS_NC);
}


// Rx and Tx descriptors have the same max size for their associated buffers
#define OX820_GMAC_MAX_DESCRIPTOR_SHIFT		11
#define OX820_GMAC_MAX_DESCRIPTOR_LENGTH	((1 << OX820_GMAC_MAX_DESCRIPTOR_SHIFT) - 1)

// Round down to nearest quad length
#define OX820_GMAC_MAX_PACKET_FRAGMENT_LENGTH 	((OX820_GMAC_MAX_DESCRIPTOR_LENGTH >> 2) << 2)


/* registers */
struct ox820_gmac_macaddress_registers_t
{
	u32         high;
	u32         low;
};

struct ox820_gmac_registers_t
{
	u32         mac_config;                 /* +0x0000 */
	u32         mac_frame_filter;           /* +0x0004 */
	u32         hash_table_high;            /* +0x0008 */
	u32         hash_table_low;             /* +0x000C */
	u32         gmii_address;               /* +0x0010 */
	u32         gmii_data;                  /* +0x0014 */
	u32         flow_control;               /* +0x0018 */
	u32         vlan_tag;                   /* +0x001C */
	u32         version;                    /* +0x0020 */
	u32         debug;                      /* +0x0024 */
	u32         remote_wakeup;              /* +0x0028 */
	u32         pmt_control_status;         /* +0x002C */
	u32         reserved_0[2];              /* +0x0030 */
	u32         interrupt_status;           /* +0x0034 */
	u32         interrupt_mask;             /* +0x0038 */
	u32         reserved_1;                 /* +0x003C */
	struct ox820_gmac_macaddress_registers_t   mac_addr[16];   /* +0x0040 */
	u32         an_control;                 /* +0x00C0 */
	u32         an_status;                  /* +0x00C4 */
	u32         an_advert;                  /* +0x00C8 */
	u32         an_lpa;                     /* +0x00CC */
	u32         an_exp;                     /* +0x00D0 */
	u32         tbi_ext_status;             /* +0x00D4 */
	volatile u32 mii_status;                /* +0x00D8 keep the optimization from optimizing the reads we do */
	u32         reserved_2[9];              /* +0x00DC */
	u32	    mmc_control;		/* +0x0100 */
	u32	    mmc_rx_int;			/* +0x0104 */
	u32         mmc_tx_int;			/* +0x0108 */
	u32         mmc_rx_mask;		/* +0x010C */
	u32         mmc_tx_mask;		/* +0x0110 */
	u32         mmc_regs[123];              /* +0x0114 */
	u32         reserved_3[256];            /* +0x0300 */
	u32         ts_control;                 /* +0x0700 */
	u32         ts_subsec_inc;              /* +0x0704 */
	u32         ts_seconds;                 /* +0x0708 */
	u32         ts_nanosecs;                /* +0x070C */
	u32         ts_sec_update;              /* +0x0710 */
	u32         ts_nanosec_update;          /* +0x0714 */
	u32         ts_addend;                  /* +0x0718 */
	u32         ts_target_time_sec;         /* +0x071C */
	u32         ts_target_time_nanosec;     /* +0x0720 */
	u32         ts_higher_word_seconds;     /* +0x0724 */
	u32         ts_status;                  /* +0x0728 */
	u32         ts_pps_control;             /* +0x072C */
	u32         ts_aux_tstamp_nanosec;      /* +0x0730 */
	u32         ts_aux_tstamp_sec;          /* +0x0734 */
	u32         reserved_4[50];             /* +0x0738 */
	struct ox820_gmac_macaddress_registers_t   mac_addr2[16]; /* +0x0800 */
	u32         reserved_5[480];            /* +0x0880 */
	u32         dma_bus_mode;               /* +0x1000 */
	u32         dma_tx_poll_demand;         /* +0x1004 */
	u32         dma_rx_poll_demand;         /* +0x1008 */
	u32         dma_rx_descriptor_list;     /* +0x100C */
	u32         dma_tx_descriptor_list;     /* +0x1010 */
	volatile u32 dma_status;                /* +0x1014 keep the optimizer from optimizing away write back same value */
	u32         dma_opmode;                 /* +0x1018 */
	u32         dma_intenable;              /* +0x101C */
	u32         dma_miss_frame_bufovfl_cnt; /* +0x1020 */
	u32         dma_rx_int_wdog_timer;      /* +0x1024 */
	u32         reserved_6[8];              /* +0x1028 */
	u32         dma_cur_host_tx_desc;       /* +0x1048 */
	u32         dma_cur_host_rx_desc;       /* +0x104C */
	u32         dma_cur_host_tx_bufadr;     /* +0x1050 */
	u32         dma_cur_host_rx_bufadr;     /* +0x1054 */
	u32         hw_feature;                 /* +0x1058 */
};

/* mac_config */
#define MSK_OX820_GMAC_MAC_CONFIG_SFTERR                0x04000000
#define BIT_OX820_GMAC_MAC_CONFIG_SFTERR                26

#define MSK_OX820_GMAC_MAC_CONFIG_CST                   0x02000000
#define BIT_OX820_GMAC_MAC_CONFIG_CST                   25

#define MSK_OX820_GMAC_MAC_CONFIG_TC                    0x01000000
#define BIT_OX820_GMAC_MAC_CONFIG_TC                    24

#define MSK_OX820_GMAC_MAC_CONFIG_WD                    0x00800000
#define BIT_OX820_GMAC_MAC_CONFIG_WD                    23

#define MSK_OX820_GMAC_MAC_CONFIG_JD                    0x00400000
#define BIT_OX820_GMAC_MAC_CONFIG_JD                    22

#define MSK_OX820_GMAC_MAC_CONFIG_BE                    0x00200000
#define BIT_OX820_GMAC_MAC_CONFIG_BE                    21

#define MSK_OX820_GMAC_MAC_CONFIG_JE                    0x00100000
#define BIT_OX820_GMAC_MAC_CONFIG_JE                    20

#define MSK_OX820_GMAC_MAC_CONFIG_IFG                   0x000E0000
#define BIT_OX820_GMAC_MAC_CONFIG_IFG                   17

#define MSK_OX820_GMAC_MAC_CONFIG_DCRS                  0x00010000
#define BIT_OX820_GMAC_MAC_CONFIG_DCRS                  16

#define MSK_OX820_GMAC_MAC_CONFIG_PS                    0x00008000
#define BIT_OX820_GMAC_MAC_CONFIG_PS                    15

#define MSK_OX820_GMAC_MAC_CONFIG_FES                   0x00004000
#define BIT_OX820_GMAC_MAC_CONFIG_FES                   14

#define MSK_OX820_GMAC_MAC_CONFIG_DO                    0x00002000
#define BIT_OX820_GMAC_MAC_CONFIG_DO                    13

#define MSK_OX820_GMAC_MAC_CONFIG_LM                    0x00001000
#define BIT_OX820_GMAC_MAC_CONFIG_LM                    12

#define MSK_OX820_GMAC_MAC_CONFIG_DM                    0x00000800
#define BIT_OX820_GMAC_MAC_CONFIG_DM                    11

#define MSK_OX820_GMAC_MAC_CONFIG_IPC                   0x00000400
#define BIT_OX820_GMAC_MAC_CONFIG_IPC                   10

#define MSK_OX820_GMAC_MAC_CONFIG_DR                    0x00000200
#define BIT_OX820_GMAC_MAC_CONFIG_DR                    9

#define MSK_OX820_GMAC_MAC_CONFIG_LUD                   0x00000100
#define BIT_OX820_GMAC_MAC_CONFIG_LUD                   8

#define MSK_OX820_GMAC_MAC_CONFIG_ACS                   0x00000080
#define BIT_OX820_GMAC_MAC_CONFIG_ACS                   7

#define MSK_OX820_GMAC_MAC_CONFIG_BL                    0x00000060
#define BIT_OX820_GMAC_MAC_CONFIG_BL                    5

#define MSK_OX820_GMAC_MAC_CONFIG_DC                    0x00000010
#define BIT_OX820_GMAC_MAC_CONFIG_DC                    4

#define MSK_OX820_GMAC_MAC_CONFIG_TE                    0x00000008
#define BIT_OX820_GMAC_MAC_CONFIG_TE                    3

#define MSK_OX820_GMAC_MAC_CONFIG_RE                    0x00000004
#define BIT_OX820_GMAC_MAC_CONFIG_RE                    2

/* mac_frame_filter */
#define MSK_OX820_GMAC_MAC_FRAME_FILTER_RA              0x80000000
#define BIT_OX820_GMAC_MAC_FRAME_FILTER_RA              31

#define MSK_OX820_GMAC_MAC_FRAME_FILTER_HPF             0x00000400
#define BIT_OX820_GMAC_MAC_FRAME_FILTER_HPF             10

#define MSK_OX820_GMAC_MAC_FRAME_FILTER_SAF             0x00000200
#define BIT_OX820_GMAC_MAC_FRAME_FILTER_SAF             9

#define MSK_OX820_GMAC_MAC_FRAME_FILTER_SAIF            0x00000100
#define BIT_OX820_GMAC_MAC_FRAME_FILTER_SAIF            8

#define MSK_OX820_GMAC_MAC_FRAME_FILTER_PCF             0x000000C0
#define BIT_OX820_GMAC_MAC_FRAME_FILTER_PCF             6

#define MSK_OX820_GMAC_MAC_FRAME_FILTER_DBF             0x00000020
#define BIT_OX820_GMAC_MAC_FRAME_FILTER_DBF             5

#define MSK_OX820_GMAC_MAC_FRAME_FILTER_PM              0x00000010
#define BIT_OX820_GMAC_MAC_FRAME_FILTER_PM              4

#define MSK_OX820_GMAC_MAC_FRAME_FILTER_DAIF            0x00000008
#define BIT_OX820_GMAC_MAC_FRAME_FILTER_DAIF            3

#define MSK_OX820_GMAC_MAC_FRAME_FILTER_HMC             0x00000004
#define BIT_OX820_GMAC_MAC_FRAME_FILTER_HMC             2

#define MSK_OX820_GMAC_MAC_FRAME_FILTER_HUC             0x00000002
#define BIT_OX820_GMAC_MAC_FRAME_FILTER_HUC             1

#define MSK_OX820_GMAC_MAC_FRAME_FILTER_PR              0x00000001
#define BIT_OX820_GMAC_MAC_FRAME_FILTER_PR              0

/* gmii_address */
#define MSK_OX820_GMAC_GMII_ADDR_PA                     0x0000F800
#define BIT_OX820_GMAC_GMII_ADDR_PA                     11

#define MSK_OX820_GMAC_GMII_ADDR_GR                     0x000007C0
#define BIT_OX820_GMAC_GMII_ADDR_GR                     6

#define MSK_OX820_GMAC_GMII_ADDR_CR                     0x0000003C
#define BIT_OX820_GMAC_GMII_ADDR_CR                     2

#define MSK_OX820_GMAC_GMII_ADDR_GW                     0x00000002
#define BIT_OX820_GMAC_GMII_ADDR_GW                     1

#define MSK_OX820_GMAC_GMII_ADDR_GB                     0x00000001
#define BIT_OX820_GMAC_GMII_ADDR_GB                     0

/* flow_control */
#define MSK_OX820_GMAC_FLOW_CONTROL_PT                  0xFFFF0000
#define BIT_OX820_GMAC_FLOW_CONTROL_PT                  16

#define MSK_OX820_GMAC_FLOW_CONTROL_DZPQ                0x00000080
#define BIT_OX820_GMAC_FLOW_CONTROL_DZPQ                7

#define MSK_OX820_GMAC_FLOW_CONTROL_PLT                 0x00000030
#define BIT_OX820_GMAC_FLOW_CONTROL_PLT                 4

#define MSK_OX820_GMAC_FLOW_CONTROL_UP                  0x00000008
#define BIT_OX820_GMAC_FLOW_CONTROL_UP                  3

#define MSK_OX820_GMAC_FLOW_CONTROL_RFE                 0x00000004
#define BIT_OX820_GMAC_FLOW_CONTROL_RFE                 2

#define MSK_OX820_GMAC_FLOW_CONTROL_TFE                 0x00000002
#define BIT_OX820_GMAC_FLOW_CONTROL_TFE                 1

#define MSK_OX820_GMAC_FLOW_CONTROL_FCB_BPA             0x00000001
#define BIT_OX820_GMAC_FLOW_CONTROL_FCB_BPA             0

/* vlan_tag */
#define MSK_OX820_GMAC_VLAN_TAG_ETV                     0x00010000
#define BIT_OX820_GMAC_VLAN_TAG_ETV                     16

#define MSK_OX820_GMAC_VLAN_TAG_VL                      0x0000FFFF
#define BIT_OX820_GMAC_VLAN_TAG_VL                      0

/* pmt_control_and_status */
#define MSK_OX820_GMAC_PMT_WAKEUP_FRAME_FILTER_RESET    0x80000000
#define BIT_OX820_GMAC_PMT_WAKEUP_FRAME_FILTER_RESET    31

#define MSK_OX820_GMAC_PMT_GLOBAL_UNICAST               0x00000200
#define BIT_OX820_GMAC_PMT_GLOBAL_UNICAST               9

#define MSK_OX820_GMAC_PMT_WAKEUP_FRAME_RECEIVED        0x00000040
#define BIT_OX820_GMAC_PMT_WAKEUP_FRAME_RECEIVED        6

#define MSK_OX820_GMAC_PMT_MAGIC_PACKET_RECEIVED        0x00000020
#define BIT_OX820_GMAC_PMT_MAGIC_PACKET_RECEIVED        5

#define MSK_OX820_GMAC_PMT_WAKEUP_FRAME_ENABLE          0x00000004
#define BIT_OX820_GMAC_PMT_WAKEUP_FRAME_ENABLE          2

#define MSK_OX820_GMAC_PMT_MAGIC_PACKET_ENABLE          0x00000002
#define BIT_OX820_GMAC_PMT_MAGIC_PACKET_ENABLE          1

#define MSK_OX820_GMAC_PMT_POWERDOWN                    0x00000001
#define BIT_OX820_GMAC_PMT_POWERDOWN                    0

/* interrupts */
#define MSK_OX820_GMAC_IRQ_TIMESTAMP                    0x00000200
#define BIT_OX820_GMAC_IRQ_TIMESTAMP                    9

#define MSK_OX820_GMAC_IRQ_MMC_RCO                      0x00000080
#define BIT_OX820_GMAC_IRQ_MMC_RCO                      7

#define MSK_OX820_GMAC_IRQ_MMC_TX                       0x00000040
#define BIT_OX820_GMAC_IRQ_MMC_TX                       6

#define MSK_OX820_GMAC_IRQ_MMC_RX                       0x00000020
#define BIT_OX820_GMAC_IRQ_MMC_RX                       5

#define MSK_OX820_GMAC_IRQ_MMC                          0x00000010
#define BIT_OX820_GMAC_IRQ_MMC                          4

#define MSK_OX820_GMAC_IRQ_PMT                          0x00000008
#define BIT_OX820_GMAC_IRQ_PMT                          3

#define MSK_OX820_GMAC_IRQ_PCS_AN_COMPLETE              0x00000004
#define BIT_OX820_GMAC_IRQ_PCS_AN_COMPLETE              2

#define MSK_OX820_GMAC_IRQ_PCS_LINK_STATUS_CHGD         0x00000002
#define BIT_OX820_GMAC_IRQ_PCS_LINK_STATUS_CHGD         1

#define MSK_OX820_GMAC_IRQ_RGMII_SMII                   0x00000001
#define BIT_OX820_GMAC_IRQ_RGMII_SMII                   0

/* mac_addr high register */
/* Bits 31-16 are only available on mac_addr[1-15] and mac_addr2 */
#define MSK_OX820_GMAC_MAC_ADDR_AE                      0x80000000
#define BIT_OX820_GMAC_MAC_ADDR_AE                      31

#define MSK_OX820_GMAC_MAC_ADDR_SA                      0x40000000
#define BIT_OX820_GMAC_MAC_ADDR_SA                      30

#define MSK_OX820_GMAC_MAC_ADDR_MBC                     0x3F000000
#define BIT_OX820_GMAC_MAC_ADDR_MBC                     24
#define MSK_OX820_GMAC_MAC_ADDR_MBC_IGNORE_47_40        0x20000000
#define MSK_OX820_GMAC_MAC_ADDR_MBC_IGNORE_39_32        0x10000000
#define MSK_OX820_GMAC_MAC_ADDR_MBC_IGNORE_31_24        0x08000000
#define MSK_OX820_GMAC_MAC_ADDR_MBC_IGNORE_23_16        0x04000000
#define MSK_OX820_GMAC_MAC_ADDR_MBC_IGNORE_15_8         0x02000000
#define MSK_OX820_GMAC_MAC_ADDR_MBC_IGNORE_7_0          0x01000000

#define MSK_OX820_GMAC_MAC_ADDR_47_32                   0x0000FFFF
#define BIT_OX820_GMAC_MAC_ADDR_47_32                   0

/* mac_addr low register */
#define MSK_OX820_GMAC_MAC_ADDR_31_0                    0xFFFFFFFF
#define BIT_OX820_GMAC_MAC_ADDR_31_0                    0

/* an_control */
#define MSK_OX820_GMAC_AN_CONTROL_SGMII_RAL_CONTROL     0x00040000
#define BIT_OX820_GMAC_AN_CONTROL_SGMII_RAL_CONTROL     18

#define MSK_OX820_GMAC_AN_CONTROL_LR                    0x00020000
#define BIT_OX820_GMAC_AN_CONTROL_LR                    17

#define MSK_OX820_GMAC_AN_CONTROL_ECD                   0x00010000
#define BIT_OX820_GMAC_AN_CONTROL_ECD                   16

#define MSK_OX820_GMAC_AN_CONTROL_ELE                   0x00004000
#define BIT_OX820_GMAC_AN_CONTROL_ELE                   14

#define MSK_OX820_GMAC_AN_CONTROL_ANE                   0x00001000
#define BIT_OX820_GMAC_AN_CONTROL_ANE                   12

#define MSK_OX820_GMAC_AN_CONTROL_RAN                   0x00000200
#define BIT_OX820_GMAC_AN_CONTROL_RAN                   9

/* an_status */
#define MSK_OX820_GMAC_AN_STATUS_ES                     0x00000100
#define BIT_OX820_GMAC_AN_STATUS_ES                     8

#define MSK_OX820_GMAC_AN_STATUS_ANC                    0x00000020
#define BIT_OX820_GMAC_AN_STATUS_ANC                    5

#define MSK_OX820_GMAC_AN_STATUS_ANA                    0x00000008
#define BIT_OX820_GMAC_AN_STATUS_ANA                    3

#define MSK_OX820_GMAC_AN_STATUS_LS                     0x00000004
#define BIT_OX820_GMAC_AN_STATUS_LS                     2

/* mii_status */
#define MSK_OX820_GMAC_MII_STATUS_FCD                   0x00000020
#define BIT_OX820_GMAC_MII_STATUS_FCD                   5

#define MSK_OX820_GMAC_MII_STATUS_JT                    0x00000010
#define BIT_OX820_GMAC_MII_STATUS_JT                    4

#define MSK_OX820_GMAC_MII_STATUS_LINK_UP               0x00000008
#define BIT_OX820_GMAC_MII_STATUS_LINK_UP               3

#define MSK_OX820_GMAC_MII_STATUS_LINK_SPEED            0x00000006
#define BIT_OX820_GMAC_MII_STATUS_LINK_SPEED            1
#define VAL_OX820_GMAC_MII_STATUS_LINK_SPEED_2_5MHZ     0x00000000
#define VAL_OX820_GMAC_MII_STATUS_LINK_SPEED_25MHZ      0x00000002
#define VAL_OX820_GMAC_MII_STATUS_LINK_SPEED_125MHZ     0x00000004

#define MSK_OX820_GMAC_MII_STATUS_LINK_MODE             0x00000001
#define BIT_OX820_GMAC_MII_STATUS_LINK_MODE             0

/* dma_bus_mode */
#define MSK_OX820_GMAC_DMA_BUS_MODE_MB                  0x04000000
#define BIT_OX820_GMAC_DMA_BUS_MODE_MB                  26
#define MSK_OX820_GMAC_DMA_BUS_MODE_AAL                 0x02000000
#define BIT_OX820_GMAC_DMA_BUS_MODE_AAL                 25
#define MSK_OX820_GMAC_DMA_BUS_MODE_8PBL                0x01000000
#define BIT_OX820_GMAC_DMA_BUS_MODE_8PBL                24
#define MSK_OX820_GMAC_DMA_BUS_MODE_USP                 0x00800000
#define BIT_OX820_GMAC_DMA_BUS_MODE_USP                 23
#define MSK_OX820_GMAC_DMA_BUS_MODE_RPBL                0x003E0000
#define BIT_OX820_GMAC_DMA_BUS_MODE_RPBL                17
#define MSK_OX820_GMAC_DMA_BUS_MODE_FB                  0x00010000
#define BIT_OX820_GMAC_DMA_BUS_MODE_FB                  16
#define MSK_OX820_GMAC_DMA_BUS_MODE_PR                  0x0000C000
#define BIT_OX820_GMAC_DMA_BUS_MODE_PR                  14
#define MSK_OX820_GMAC_DMA_BUS_MODE_PBL                 0x00003F00
#define BIT_OX820_GMAC_DMA_BUS_MODE_PBL                 12
#define MSK_OX820_GMAC_DMA_BUS_MODE_DSL                 0x0000007C
#define BIT_OX820_GMAC_DMA_BUS_MODE_DSL                 2
#define MSK_OX820_GMAC_DMA_BUS_MODE_DA                  0x00000002
#define BIT_OX820_GMAC_DMA_BUS_MODE_DA                  1
#define MSK_OX820_GMAC_DMA_BUS_MODE_SWR                 0x00000001
#define BIT_OX820_GMAC_DMA_BUS_MODE_SWR                 0

/* dma_status */
#define MSK_OX820_GMAC_DMA_STATUS_TTI                   0x20000000
#define BIT_OX820_GMAC_DMA_STATUS_TTI                   29
#define MSK_OX820_GMAC_DMA_STATUS_GPI                   0x10000000
#define BIT_OX820_GMAC_DMA_STATUS_GPI                   28
#define MSK_OX820_GMAC_DMA_STATUS_GMI                   0x08000000
#define BIT_OX820_GMAC_DMA_STATUS_GMI                   27
#define MSK_OX820_GMAC_DMA_STATUS_GLI                   0x04000000
#define BIT_OX820_GMAC_DMA_STATUS_GLI                   26
#define MSK_OX820_GMAC_DMA_STATUS_EB                    0x03800000
#define BIT_OX820_GMAC_DMA_STATUS_EB                    23
#define MSK_OX820_GMAC_DMA_STATUS_TS                    0x00700000
#define BIT_OX820_GMAC_DMA_STATUS_TS                    20
#define VAL_OX820_GMAC_DMA_STATUS_TS_STOPPED		0x00000000
#define VAL_OX820_GMAC_DMA_STATUS_TS_FETCHING		0x00100000
#define VAL_OX820_GMAC_DMA_STATUS_TS_WAITING		0x00200000
#define VAL_OX820_GMAC_DMA_STATUS_TS_READING		0x00300000
#define VAL_OX820_GMAC_DMA_STATUS_TS_FLUSHING		0x00400000
#define VAL_OX820_GMAC_DMA_STATUS_TS_RESERVED		0x00500000
#define VAL_OX820_GMAC_DMA_STATUS_TS_SUSPENDED		0x00600000
#define VAL_OX820_GMAC_DMA_STATUS_TS_CLOSING		0x00700000
#define MSK_OX820_GMAC_DMA_STATUS_RS                    0x000E0000
#define BIT_OX820_GMAC_DMA_STATUS_RS                    17
#define VAL_OX820_GMAC_DMA_STATUS_RS_STOPPED		0x00000000
#define VAL_OX820_GMAC_DMA_STATUS_RS_FETCHING		0x00020000
#define VAL_OX820_GMAC_DMA_STATUS_RS_RESERVED_2		0x00040000
#define VAL_OX820_GMAC_DMA_STATUS_RS_WAITING		0x00060000
#define VAL_OX820_GMAC_DMA_STATUS_RS_SUSPENDED		0x00080000
#define VAL_OX820_GMAC_DMA_STATUS_RS_CLOSING		0x000A0000
#define VAL_OX820_GMAC_DMA_STATUS_RS_RESERVED_6		0x000C0000
#define VAL_OX820_GMAC_DMA_STATUS_RS_TRANSFERRING	0x000E0000
#define MSK_OX820_GMAC_DMA_STATUS_NIP                   0x00010000
#define BIT_OX820_GMAC_DMA_STATUS_NIP                   16
#define MSK_OX820_GMAC_DMA_STATUS_AIS                   0x00008000
#define BIT_OX820_GMAC_DMA_STATUS_AIS                   15
#define MSK_OX820_GMAC_DMA_STATUS_ERI                   0x00004000
#define BIT_OX820_GMAC_DMA_STATUS_ERI                   14
#define MSK_OX820_GMAC_DMA_STATUS_FBI                   0x00002000
#define BIT_OX820_GMAC_DMA_STATUS_FBI                   13
#define MSK_OX820_GMAC_DMA_STATUS_ETI                   0x00000400
#define BIT_OX820_GMAC_DMA_STATUS_ETI                   10
#define MSK_OX820_GMAC_DMA_STATUS_RWT                   0x00000200
#define BIT_OX820_GMAC_DMA_STATUS_RWT                   9
#define MSK_OX820_GMAC_DMA_STATUS_RPS                   0x00000100
#define BIT_OX820_GMAC_DMA_STATUS_RPS                   8
#define MSK_OX820_GMAC_DMA_STATUS_RU                    0x00000080
#define BIT_OX820_GMAC_DMA_STATUS_RU                    7
#define MSK_OX820_GMAC_DMA_STATUS_RI                    0x00000040
#define BIT_OX820_GMAC_DMA_STATUS_RI                    6
#define MSK_OX820_GMAC_DMA_STATUS_UNF                   0x00000020
#define BIT_OX820_GMAC_DMA_STATUS_UNF                   5
#define MSK_OX820_GMAC_DMA_STATUS_OVF                   0x00000010
#define BIT_OX820_GMAC_DMA_STATUS_OVF                   4
#define MSK_OX820_GMAC_DMA_STATUS_TJT                   0x00000008
#define BIT_OX820_GMAC_DMA_STATUS_TJT                   3
#define MSK_OX820_GMAC_DMA_STATUS_TU                    0x00000004
#define BIT_OX820_GMAC_DMA_STATUS_TU                    2
#define MSK_OX820_GMAC_DMA_STATUS_TPS                   0x00000002
#define BIT_OX820_GMAC_DMA_STATUS_TPS                   1
#define MSK_OX820_GMAC_DMA_STATUS_TI                    0x00000001
#define BIT_OX820_GMAC_DMA_STATUS_TI                    0

/* dma_opmode */
#define MSK_OX820_GMAC_DMA_OPMODE_DT                    0x04000000
#define BIT_OX820_GMAC_DMA_OPMODE_DT                    26
#define MSK_OX820_GMAC_DMA_OPMODE_RSF                   0x02000000
#define BIT_OX820_GMAC_DMA_OPMODE_RSF                   25
#define MSK_OX820_GMAC_DMA_OPMODE_DFF                   0x01000000
#define BIT_OX820_GMAC_DMA_OPMODE_DFF                   24
#define MSK_OX820_GMAC_DMA_OPMODE_RFA2                  0x00800000
#define BIT_OX820_GMAC_DMA_OPMODE_RFA2                  23
#define MSK_OX820_GMAC_DMA_OPMODE_RFD2                  0x00400000
#define BIT_OX820_GMAC_DMA_OPMODE_RFD2                  22
#define MSK_OX820_GMAC_DMA_OPMODE_TSF                   0x00200000
#define BIT_OX820_GMAC_DMA_OPMODE_TSF                   21
#define MSK_OX820_GMAC_DMA_OPMODE_TTC                   0x0001C000
#define BIT_OX820_GMAC_DMA_OPMODE_TTC                   14
#define VAL_OX820_GMAC_DMA_OPMODE_TTC_16		0x0001C000
#define VAL_OX820_GMAC_DMA_OPMODE_TTC_24		0x00018000
#define VAL_OX820_GMAC_DMA_OPMODE_TTC_32		0x00014000
#define VAL_OX820_GMAC_DMA_OPMODE_TTC_40		0x00010000
#define VAL_OX820_GMAC_DMA_OPMODE_TTC_256		0x0000C000
#define VAL_OX820_GMAC_DMA_OPMODE_TTC_192		0x00008000
#define VAL_OX820_GMAC_DMA_OPMODE_TTC_128		0x00004000
#define VAL_OX820_GMAC_DMA_OPMODE_TTC_64		0x00000000
#define MSK_OX820_GMAC_DMA_OPMODE_ST                    0x00004000
#define BIT_OX820_GMAC_DMA_OPMODE_ST                    13
#define MSK_OX820_GMAC_DMA_OPMODE_RFD                   0x00003000
#define BIT_OX820_GMAC_DMA_OPMODE_RFD                   11
#define MSK_OX820_GMAC_DMA_OPMODE_RFA                   0x00001E00
#define BIT_OX820_GMAC_DMA_OPMODE_RFA                   9
#define MSK_OX820_GMAC_DMA_OPMODE_EFC                   0x00000100
#define BIT_OX820_GMAC_DMA_OPMODE_EFC                   8
#define MSK_OX820_GMAC_DMA_OPMODE_FEF                   0x00000080
#define BIT_OX820_GMAC_DMA_OPMODE_FEF                   7
#define MSK_OX820_GMAC_DMA_OPMODE_FUF                   0x00000040
#define BIT_OX820_GMAC_DMA_OPMODE_FUF                   6
#define MSK_OX820_GMAC_DMA_OPMODE_RTC                   0x00000018
#define BIT_OX820_GMAC_DMA_OPMODE_RTC                   3
#define VAL_OX820_GMAC_DMA_OPMODE_RTC_64		0x00000000
#define VAL_OX820_GMAC_DMA_OPMODE_RTC_32		0x00000008
#define VAL_OX820_GMAC_DMA_OPMODE_RTC_96		0x00000010
#define VAL_OX820_GMAC_DMA_OPMODE_RTC_128		0x00000018
#define MSK_OX820_GMAC_DMA_OPMODE_OSF                   0x00000004
#define BIT_OX820_GMAC_DMA_OPMODE_OSF                   2
#define MSK_OX820_GMAC_DMA_OPMODE_SR                    0x00000002
#define BIT_OX820_GMAC_DMA_OPMODE_SR			1

/* dma_intenable */
#define MSK_OX820_GMAC_DMA_INTENABLE_NIE                0x00010000
#define BIT_OX820_GMAC_DMA_INTENABLE_NIE                16
#define MSK_OX820_GMAC_DMA_INTENABLE_AIE                0x00008000
#define BIT_OX820_GMAC_DMA_INTENABLE_AIE                15
#define MSK_OX820_GMAC_DMA_INTENABLE_ERE                0x00004000
#define BIT_OX820_GMAC_DMA_INTENABLE_ERE                14
#define MSK_OX820_GMAC_DMA_INTENABLE_FBE                0x00002000
#define BIT_OX820_GMAC_DMA_INTENBALE_FBE                13
#define MSK_OX820_GMAC_DMA_INTENABLE_ETE                0x00000400
#define BIT_OX820_GMAC_DMA_INTENABLE_ETE                10
#define MSK_OX820_GMAC_DMA_INTENBALE_RWE                0x00000200
#define BIT_OX820_GMAC_DMA_INTENBALE_RWE                9
#define MSK_OX820_GMAC_DMA_INTENABLE_RSE                0x00000100
#define BIT_OX820_GMAC_DMA_INTENABLE_RSE                8
#define MSK_OX820_GMAC_DMA_INTENABLE_RUE                0x00000080
#define BIT_OX820_GMAC_DMA_INTENABLE_RUE                7
#define MSK_OX820_GMAC_DMA_INTENABLE_RIE                0x00000040
#define BIT_OX820_GMAC_DMA_INTENABLE_RIE                6
#define MSK_OX820_GMAC_DMA_INTENABLE_UNE                0x00000020
#define BIT_OX820_GMAC_DMA_INTENABLE_UNE                5
#define MSK_OX820_GMAC_DMA_INTENABLE_OVE                0x00000010
#define BIT_OX820_GMAC_DMA_INTENABLE_OVE                4
#define MSK_OX820_GMAC_DMA_INTENABLE_TUJ                0x00000008
#define BIT_OX820_GMAC_DMA_INTENABLE_TUJ                3
#define MSK_OX820_GMAC_DMA_INTENABLE_TUE                0x00000004
#define BIT_OX820_GMAC_DMA_INTENABLE_TUE                2
#define MSK_OX820_GMAC_DMA_INTENABLE_TSE                0x00000002
#define BIT_OX820_GMAC_DMA_INTENABLE_TSE                1
#define MSK_OX820_GMAC_DMA_INTENABLE_TIE                0x00000001
#define BIT_OX820_GMAC_DMA_INTENABLE_TIE                0

/* hw_feature */
#define MSK_OX820_GMAC_HW_FEATURE_ALTERNATE             0x01000000
#define BIT_OX820_GMAC_HW_FEATURE_ALTERNATE             24
#define MSK_OX820_GMAC_HW_FEATURE_RXFIFO_LARGER_2048B   0x00080000
#define BIT_OX820_GMAC_HW_FEATURE_RXFIFO_LARGER_2048B   19
#define MSK_OX820_GMAC_HW_FEATURE_IP_CHECKSUM_OFFLOAD2  0x00040000
#define BIT_OX820_GMAC_HW_FEATURE_IP_CHECKSUM_OFFLOAD2  18
#define MSK_OX820_GMAC_HW_FEATURE_IP_CHECKSUM_OFFLOAD1  0x00020000
#define BIT_OX820_GMAC_HW_FEATURE_IP_CHECKSUM_OFFLAOD1  17
#define MSK_OX820_GMAC_HW_FEATURE_TX_CHECKSUM_OFFLOAD   0x00010000
#define BIT_OX820_GMAC_HW_FEATURE_TX_CHECKSUM_OFFLAOD   16
#define MSK_OX820_GMAC_HW_FEATURE_IEEE1588_2008         0x00002000
#define BIT_OX820_GMAC_HW_FEATURE_IEEE1588_2008         13
#define MSK_OX820_GMAC_HW_FEATURE_IEEE1588_2002         0x00001000
#define BIT_OX820_GMAC_HW_FEATURE_IEEE1588_2002         12
#define MSK_OX820_GMAC_HW_FEATURE_RMON                  0x00000800
#define BIT_OX820_GMAC_HW_FEATURE_RMON                  11
#define MSK_OX820_GMAC_HW_FEATURE_PMT_MAGIC_PACKET      0x00000400
#define BIT_OX820_GMAC_HW_FEATURE_PMT_MAGIC_PACKET      10
#define MSK_OX820_GMAC_HW_FEATURE_PMT_REMOTE_WAKEUP     0x00000200
#define BIT_OX820_GMAC_HW_FEATURE_PMT_REMOTE_WAKEUP     9
#define MSK_OX820_GMAC_HW_FEATURE_SMA                   0x00000100
#define BIT_OX820_GMAC_HW_FEATURE_SMA                   8
#define MSK_OX820_GMAC_HW_FEATURE_PCS                   0x00000040
#define BIT_OX820_GMAC_HW_FEATURE_PCS                   6
#define MSK_OX820_GMAC_HW_FEATURE_HASH                  0x00000020
#define BIT_OX820_GMAC_HW_FEATURE_HASH                  5
#define MSK_OX820_GMAC_HW_FEATURE_1000MBPS              0x00000002
#define BIT_OX820_GMAC_HW_FEATURE_1000MBPS              1
#define MSK_OX820_GMAC_HW_FEATURE_10_100MBPS            0x00000001
#define BIT_OX820_GMAC_HW_FEATURE_10_100MBPS            0

/* interrupt_status */
#define MSK_OX820_GMAC_INT_STATUS_TIMESTAMP 		0x00000200
#define BIT_OX820_GMAC_INT_STATUS_TIMESTAMP 		9
#define MSK_OX820_GMAC_INT_STATUS_MMC_RX_CHKSUM_OFFLOAD	0x00000080
#define BIT_OX820_GMAC_INT_STATUS_MMC_RX_CHKSUM_OFFLOAD	7
#define MSK_OX820_GMAC_INT_STATUS_MMC_TRANSMIT		0x00000040
#define BIT_OX820_GMAC_INT_STATUS_MMC_TRANSMIT		6
#define MSK_OX820_GMAC_INT_STATUS_MMC_RECEIVE		0x00000020
#define BIT_OX820_GMAC_INT_STATUS_MMC_RECEIVE		5
#define MSK_OX820_GMAC_INT_STATUS_MMC			0x00000010
#define BIT_OX820_GMAC_INT_STATUS_MMC			4
#define MSK_OX820_GMAC_INT_STATUS_PMT			0x00000008
#define BIT_OX820_GMAC_INT_STATUS_PMT			3
#define MSK_OX820_GMAC_INT_STATUS_PCS_AN_COMPLETE	0x00000004
#define BIT_OX820_GMAC_INT_STATUS_PCS_AN_COMPLETE	2
#define MSK_OX820_GMAC_INT_STATUS_PCS_LNK_STAT_CHGD	0x00000002
#define BIT_OX820_GMAC_INT_STATUS_PCS_LNK_STAT_CHGD	1
#define MSK_OX820_GMAC_INT_STATUS_RGMII_SMII		0x00000001
#define BIT_OX820_GMAC_INT_STATUS_RGMII_SMII		0

#endif
