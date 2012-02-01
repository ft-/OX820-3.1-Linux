/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _ox820_hw_sysctrl_h
#define _ox820_hw_sysctrl_h

/* those made volatile have been specifically made that way since they are optimization-sensitive */
struct ox820_sysctrl_registers_t
{
	u32 reserved_0[5];                  /* +0x0000 */
	u32 mfa_secsel_ctrl;                /* +0x0014 */
	u32 reserved_1[3];                  /* +0x0018 */
	volatile u32 cken_stat;             /* +0x0024 */
	volatile u32 rsten_stat;            /* +0x0028 */
	volatile u32 cken_set_ctrl;         /* +0x002C */
	volatile u32 cken_clr_ctrl;         /* +0x0030 */
	volatile u32 rsten_set_ctrl;        /* +0x0034 */
	volatile u32 rsten_clr_ctrl;        /* +0x0038 */
	u32 reserved_2;                     /* +0x003C */
	u32 usbmph_ctrl;                    /* +0x0040 */
	u32 usbmph_stat;                    /* +0x0044 */
	u32 reserved_3;                     /* +0x0048 */
	u32 sema_stat;                      /* +0x004C */
	u32 sema_set;                       /* +0x0050 */
	u32 sema_clrl;                      /* +0x0054 */
	u32 sema_maska_ctrl;                /* +0x0058 */
	u32 sema_maskb_ctrl;                /* +0x005C */
	u32 sema_maskc_ctrl;                /* +0x0060 */
   	u32 reserved_4[2];                  /* +0x0064 */
   	u32 plla_key_ctrl;                  /* +0x006C */
   	u32 audio_ctrl;                     /* +0x0070 */
   	u32 reserved_5;                     /* +0x0074 */
   	u32 gmaca_ctrl;                     /* +0x0078 */
   	u32 reserved_6;                     /* +0x007C */
   	u32 arm_stat;                       /* +0x0080 */
   	u32 usbaphy_ctrl;                   /* +0x0084 */
   	u32 usbaphy_stat;                   /* +0x0088 */
   	u32 mfa_tersel_ctrl;                /* +0x008C */
   	u32 usb_ctrl;                       /* +0x0090 */
   	u32 mfa_quatsel_ctrl;               /* +0x0094 */
   	u32 reserved_7;                     /* +0x0098 */
   	u32 mfa_debugsel_ctrl;              /* +0x009C */
   	u32 reserved_8;                     /* +0x00A0 */
   	u32 mfa_altsel_ctrl;                /* +0x00A4 */
   	u32 reserved_9;                     /* +0x00A8 */
   	u32 mfa_pullup_ctrl;                /* +0x00AC */
   	u32 reserved_10[5];                 /* +0x00B0 */
   	u32 scratchword[4];                 /* +0x00C4 */
   	u32 monmux_ctrl;                    /* +0x00D4 */
   	u32 reserved_11[5];                 /* +0x00D8 */
   	u32 gmacb_ctrl;                     /* +0x00EC */
   	u32 usbbphy_ctrl;                   /* +0x00F0 */
   	u32 usbbphy_stat;                   /* +0x00F4 */
   	u32 ref300_div_ctrl;                /* +0x00F8 */
   	u32 reserved_12;                    /* +0x00FC */
   	u32 gmaca_delay;                    /* +0x0100 */
   	u32 gmacb_delay;                    /* +0x0104 */
   	u32 gmac_dll;                       /* +0x0108 */
   	u32 gmac_samp;                      /* +0x010C */
   	u32 amba_ctrl;                      /* +0x0110 */
   	volatile u32 hcsl_ctrl;             /* +0x0114 */
   	u32 usbaphy_tune;                   /* +0x0118 */
   	u32 usbbphy_tune;                   /* +0x011C */
   	volatile u32 pciea_ctrl;            /* +0x0120 */
   	volatile u32 pcieb_ctrl;            /* +0x0124 */
   	u32 pciephy_ctrl;                   /* +0x0128 */
   	u32 reserved_13[2];                 /* +0x012C */
   	u32 ddramio_ctrl;                   /* +0x0134 */
   	u32 pciea_pom_mem_addr_offset[2];   /* +0x0138 */
   	u32 pciea_in_mem_addr_start[2];     /* +0x0140 */
   	u32 pciea_in_io_addr_start;         /* +0x0148 */
   	u32 pciea_in_cfg_addr_start[2];     /* +0x014C */
   	u32 pciea_in_msg_addr_start;        /* +0x0154 */
   	u32 pciea_in_mem_addr_limit[2];     /* +0x0158 */
   	u32 pciea_in_io_addr_limit;         /* +0x0160 */
   	u32 pciea_in_cfg_addr_limit[2];     /* +0x0164 */
   	u32 pciea_in_msg_addr_limit;        /* +0x016C */
   	u32 pciea_ahb_slave_ctrl;           /* +0x0170 */
   	u32 pcieb_pom_mem_addr_offset[2];   /* +0x0174 */
   	u32 pcieb_in_mem_addr_start[2];     /* +0x017C */
   	u32 pcieb_in_io_addr_start;         /* +0x0184 */
   	u32 pcieb_in_cfg_addr_start[2];     /* +0x0188 */
   	u32 pcieb_in_msg_addr_start;        /* +0x0190 */
   	u32 pcieb_in_mem_addr_limit[2];     /* +0x0194 */
   	u32 pcieb_in_io_addr_limit;         /* +0x019C */
   	u32 pcieb_in_cfg_addr_limit[2];     /* +0x01A0 */
   	u32 pcieb_in_msg_addr_limit;        /* +0x01A8 */
   	u32 pcieb_ahb_slave_ctrl;           /* +0x01AC */
   	u32 pciea_ahb_slave_cfg_ctrl;       /* +0x01B0 */
   	u32 pcieb_ahb_slave_cfg_ctrl;       /* +0x01B4 */
   	u32 pciea_ahb_mstr_ctrl;            /* +0x01B8 */
   	u32 pcieb_ahb_mstr_ctrl;            /* +0x01BC */
   	u32 pciea_ahb_slv_misc_info;        /* +0x01C0 */
   	u32 pcieb_ahb_slv_misc_info;        /* +0x01C4 */
   	u32 reserved_14[40];                /* +0x01C8 */
   	u32 plla_ctrl[4];                   /* +0x01F0 */
};

/* Reset Controls */
#define MSK_OX820_SYSCTRL_RSTEN_ARM_SCU         0x00000001
#define BIT_OX820_SYSCTRL_RSTEN_ARM             0
#define MSK_OX820_SYSCTRL_RSTEN_LEON            0x00000002
#define BIT_OX820_SYSCTRL_RSTEN_LEON            1
#define MSK_OX820_SYSCTRL_RSTEN_ARM_CPU0        0x00000004
#define BIT_OX820_SYSCTRL_RSTEN_ARM_CPU0        2
#define MSK_OX820_SYSCTRL_RSTEN_ARM_CPU1        0x00000008
#define BIT_OX820_SYSCTRL_RSTEN_ARM_CPU1        3
#define MSK_OX820_SYSCTRL_RSTEN_USBMPH          0x00000010
#define BIT_OX820_SYSCTRL_RSTEN_USBMPH          4
#define MSK_OX820_SYSCTRL_RSTEN_USBPHYA         0x00000020
#define BIT_OX820_SYSCTRL_RSTEN_USBPHYA         5
#define MSK_OX820_SYSCTRL_RSTEN_ETHA            0x00000040
#define BIT_OX820_SYSCTRL_RSTEN_ETHA            6
#define MSK_OX820_SYSCTRL_RSTEN_PCIEA           0x00000080
#define BIT_OX820_SYSCTRL_RSTEN_PCIEA           7
#define MSK_OX820_SYSCTRL_RSTEN_DMA_SGDMA       0x00000100
#define BIT_OX820_SYSCTRL_RSTEN_DMA_SGDMA       8
#define MSK_OX820_SYSCTRL_RSTEN_CIPHER          0x00000200
#define BIT_OX820_SYSCTRL_RSTEN_CIPHER          9
#define MSK_OX820_SYSCTRL_RSTEN_DDRAM           0x00000400
#define BIT_OX820_SYSCTRL_RSTEN_DDRAM           10
#define MSK_OX820_SYSCTRL_RSTEN_SATA            0x00000800
#define BIT_OX820_SYSCTRL_RSTEN_SATA            11
#define MSK_OX820_SYSCTRL_RSTEN_SATALINK        0x00001000
#define BIT_OX820_SYSCTRL_RSTEN_SATALINK        12
#define MSK_OX820_SYSCTRL_RSTEN_SATAPHY         0x00002000
#define BIT_OX820_SYSCTRL_RSTEN_SATAPHY         13
#define MSK_OX820_SYSCTRL_RSTEN_PCIEPHY         0x00004000
#define BIT_OX820_SYSCTRL_RSTEN_PCIEPHY         14
#define MSK_OX820_SYSCTRL_RSTEN_STATIC          0x00008000
#define BIT_OX820_SYSCTRL_RSTEN_STATIC          15
#define MSK_OX820_SYSCTRL_RSTEN_GPIO            0x00010000
#define BIT_OX820_SYSCTRL_RSTEN_GPIO            16
#define MSK_OX820_SYSCTRL_RSTEN_UARTA           0x00020000
#define BIT_OX820_SYSCTRL_RSTEN_UARTA           17
#define MSK_OX820_SYSCTRL_RSTEN_UARTB           0x00040000
#define BIT_OX820_SYSCTRL_RSTEN_UARTB           18
#define MSK_OX820_SYSCTRL_RSTEN_FAN_IRRX        0x00080000
#define BIT_OX820_SYSCTRL_RSTEN_FAN_IRRX        19
#define MSK_OX820_SYSCTRL_RSTEN_AUDIO           0x00100000
#define BIT_OX820_SYSCTRL_RSTEN_AUDIO           20
#define MSK_OX820_SYSCTRL_RSTEN_SD              0x00200000
#define BIT_OX820_SYSCTRL_RSTEN_SD              21
#define MSK_OX820_SYSCTRL_RSTEN_ETHB            0x00400000
#define BIT_OX820_SYSCTRL_RSTEN_ETHB            22
#define MSK_OX820_SYSCTRL_RSTEN_PCIEB           0x00800000
#define BIT_OX820_SYSCTRL_RSTEN_PCIEB           23
#define MSK_OX820_SYSCTRL_RSTEN_VIDEO           0x01000000
#define BIT_OX820_SYSCTRL_RSTEN_VIDEO           24
#define MSK_OX820_SYSCTRL_RSTEN_DDRAMPHY        0x02000000
#define BIT_OX820_SYSCTRL_RSTEN_DDRAMPHY        25
#define MSK_OX820_SYSCTRL_RSTEN_USBPHYB         0x04000000
#define BIT_OX820_SYSCTRL_RSTEN_USBPHYB         26
#define MSK_OX820_SYSCTRL_RSTEN_USBDEV          0x08000000
#define BIT_OX820_SYSCTRL_RSTEN_USBDEV          27
#define MSK_OX820_SYSCTRL_RSTEN_ARM_DBG_WDOG    0x20000000
#define BIT_OX820_SYSCTRL_RSTEN_ARM_DBG_WDOG    29
#define MSK_OX820_SYSCTRL_RSTEN_PLLA            0x40000000
#define BIT_OX820_SYSCTRL_RSTEN_PLLA            30
#define MSK_OX820_SYSCTRL_RSTEN_PLLB            0x80000000
#define BIT_OX820_SYSCTRL_RSTEN_PLLB            31

/* Clock Controls */
#define MSK_OX820_SYSCTRL_CKEN_LEON             0x00000001
#define BIT_OX820_SYSCTRL_CKEN_LEON             0
#define MSK_OX820_SYSCTRL_CKEN_DMA_SGDMA        0x00000002
#define BIT_OX820_SYSCTRL_CKEN_DMA_SGDMA        1
#define MSK_OX820_SYSCTRL_CKEN_CIPHER           0x00000004
#define BIT_OX820_SYSCTRL_CKEN_CIPHER           2
#define MSK_OX820_SYSCTRL_CKEN_SD               0x00000008
#define BIT_OX820_SYSCTRL_CKEN_SD               3
#define MSK_OX820_SYSCTRL_CKEN_SATA             0x00000010
#define BIT_OX820_SYSCTRL_CKEN_SATA             4
#define MSK_OX820_SYSCTRL_CKEN_AUDIO            0x00000020
#define BIT_OX820_SYSCTRL_CKEN_AUDIO            5
#define MSK_OX820_SYSCTRL_CKEN_USBMPH           0x00000040
#define BIT_OX820_SYSCTRL_CKEN_USBMPH           6
#define MSK_OX820_SYSCTRL_CKEN_ETHA             0x00000080
#define BIT_OX820_SYSCTRL_CKEN_ETHA             7
#define MSK_OX820_SYSCTRL_CKEN_PCIEA            0x00000100
#define BIT_OX820_SYSCTRL_CKEN_PCIEA            8
#define MSK_OX820_SYSCTRL_CKEN_STATIC           0x00000200
#define BIT_OX820_SYSCTRL_CKEN_STATIC           9
#define MSK_OX820_SYSCTRL_CKEN_ETHB             0x00000400
#define BIT_OX820_SYSCTRL_CKEN_ETHB             10
#define MSK_OX820_SYSCTRL_CKEN_PCIEB            0x00000800
#define BIT_OX820_SYSCTRL_CKEN_PCIEB            11
#define MSK_OX820_SYSCTRL_CKEN_REF600           0x00001000
#define BIT_OX820_SYSCTRL_CKEN_REF600           12
#define MSK_OX820_SYSCTRL_CKEN_USBDEV           0x00002000
#define BIT_OX820_SYSCTRL_CKEN_USBDEV           13
#define MSK_OX820_SYSCTRL_CKEN_DDRAM            0x00004000
#define BIT_OX820_SYSCTRL_CKEN_DDRAM            14
#define MSK_OX820_SYSCTRL_CKEN_DDRAMPHY         0x00008000
#define BIT_OX820_SYSCTRL_CKEN_DDRAMPHY         15
#define MSK_OX820_SYSCTRL_CKEN_DDRAMCK          0x00010000
#define BIT_OX820_SYSCTRL_CKEN_DDRAMCK          16

/* pciea_ctrl, pcieb_ctrl */
#define MSK_OX820_SYSCTRL_PCIE_CTRL_OBTRANS		0x00001000
#define BIT_OX820_SYSCTRL_PCIE_CTRL_OBTRANS		12
#define MSK_OX820_SYSCTRL_PCIE_CTRL_LINK_UP		0x00000800
#define BIT_OX820_SYSCTRL_PCIE_CTRL_LINK_UP		11
#define MSK_OX820_SYSCTRL_PCIE_CTRL_READY_ENTR_L23	0x00000200
#define BIT_OX820_SYSCTRL_PCIE_CTRL_READY_ENTR_L23	9
#define MSK_OX820_SYSCTRL_PCIE_CTRL_INIT_RESET		0x00000080
#define BIT_OX820_SYSCTRL_PCIE_CTRL_INIT_RESET		7
#define MSK_OX820_SYSCTRL_PCIE_CTRL_LTSSM_ENABLE	0x00000010
#define BIT_OX820_SYSCTRL_PCIE_CTRL_LTSSM_ENABLE	4
#define MSK_OX820_SYSCTRL_PCIE_CTRL_DEVICE_TYPE		0x0000000F
#define BIT_OX820_SYSCTRL_PCIE_CTRL_DEVICE_TYPE		0
#define VAL_OX820_SYSCTRL_PCIE_CTRL_DEVICE_TYPE_ENDPOINT	0x00000000
#define VAL_OX820_SYSCTRL_PCIE_CTRL_DEVICE_TYPE_LEGACY_ENDPOINT	0x00000001
#define VAL_OX820_SYSCTRL_PCIE_CTRL_DEVICE_TYPE_ROOT		0x00000004

/* pciea_ahb_slave_ctrl, pcieb_ahb_slave_ctrl */
#define MSK_OX820_SYSCTRL_PCIE_AHB_SLAVE_CTRL_BE	0x03C00000
#define BIT_OX820_SYSCTRL_PCIE_AHB_SLAVE_CTRL_BE	22

/* usbaphy_ctrl, usbbphy_ctrl */
#define MSK_OX820_SYSCTRL_USBPHY_CTRL_SIDDQ			0x00080000
#define BIT_OX820_SYSCTRL_USBPHY_CTRL_SIDDQ			19
#define MSK_OX820_SYSCTRL_USBPHY_CTRL_LOOPBACK_ENB		0x00040000
#define BIT_OX820_SYSCTRL_USBPHY_CTRL_LOOPBACK_ENB		18
#define MSK_OX820_SYSCTRL_USBPHY_CTRL_VATEST_EN			0x00020000
#define BIT_OX820_SYSCTRL_USBPHY_CTRL_VATEST_EN			17
#define MSK_OX820_SYSCTRL_USBPHY_CTRL_SUSPENDM_MANUAL_ENABLE	0x00010000
#define BIT_OX820_SYSCTRL_USBPHY_CTRL_SUSPENDM_MANUAL_ENABLE	16
#define MSK_OX820_SYSCTRL_USBPHY_CTRL_SUSPENDM_MANUAL_STATE	0x00008000
#define BIT_OX820_SYSCTRL_USBPHY_CTRL_SUSPENDM_MANUAL_STATE	15
#define MSK_OX820_SYSCTRL_USBPHY_CTRL_ATE_RESET			0x00004000
#define BIT_OX820_SYSCTRL_USBPHY_CTRL_ATE_RESET			14
#define MSK_OX820_SYSCTRL_USBPHY_CTRL_TEST_DIN			0x00003FC0
#define BIT_OX820_SYSCTRL_USBPHY_CTRL_TEST_DIN			6
#define MSK_OX820_SYSCTRL_USBPHY_CTRL_TEST_ADDR			0x0000003C
#define BIT_OX820_SYSCTRL_USBPHY_CTRL_TEST_ADDR			2
#define MSK_OX820_SYSCTRL_USBPHY_CTRL_TEST_DOUT_SEL		0x00000002
#define BIT_OX820_SYSCTRL_USBPHY_CTRL_TEST_DOUT_SEL		1
#define MSK_OX820_SYSCTRL_USBPHY_CTRL_TEST_CLK			0x00000001
#define BIT_OX820_SYSCTRL_USBPHY_CTRL_TEST_CLK			0

/* usb_ctrl */
#define MSK_OX820_SYSCTRL_USB_CTRL_USBAPHY_CKSEL	0x00000060
#define BIT_OX820_SYSCTRL_USB_CTRL_USBAPHY_CKSEL	5
#define VAL_OX820_SYSCTRL_USB_CTRL_USBAPHY_CKSEL_XIO	0x00000000
#define VAL_OX820_SYSCTRL_USB_CTRL_USBAPHY_CKSEL_XO	0x00000020
#define VAL_OX820_SYSCTRL_USB_CTRL_USBAPHY_CKSEL_INT	0x00000040
#define MSK_OX820_SYSCTRL_USB_CTRL_USBAMUX		0x00000010
#define BIT_OX820_SYSCTRL_USB_CTRL_USBAMUX		4
#define VAL_OX820_SYSCTRL_USB_CTRL_USBAMUX_HOST		0x00000000
#define VAL_OX820_SYSCTRL_USB_CTRL_USBAMUX_DEVICE	0x00000010
#define MSK_OX820_SYSCTRL_USB_CTRL_REFCLKDIV		0x0000000C
#define VAL_OX820_SYSCTRL_USB_CTRL_REFCLKDIV_12MHZ	0x00000000
#define VAL_OX820_SYSCTRL_USB_CTRL_REFCLKDIV_24MHZ	0x00000004
#define VAL_OX820_SYSCTRL_USB_CTRL_REFCLKDIV_48MHZ	0x00000008
#define MSK_OX820_SYSCTRL_USB_CTRL_CKO_SEL		0x00000003
#define BIT_OX820_SYSCTRL_USB_CTRL_CKO_SEL		0
#define VAL_OX820_SYSCTRL_USB_CTRL_CKO_SEL_USBAPHY_XO	0x00000000
#define VAL_OX820_SYSCTRL_USB_CTRL_CKO_SEL_REF300_BCK	0x00000002
#define VAL_OX820_SYSCTRL_USB_CTRL_CKO_SEL_PLLB_BCK	0x00000003

/* usbmph_ctrl */
#define MSK_OX820_SYSCTRL_USBMPH_CTRL_OP_POL_C		0x00000020
#define BIT_OX820_SYSCTRL_USBMPH_CTRL_OP_POL_C		5
#define MSK_OX820_SYSCTRL_USBMPH_CTRL_OP_POL_B		0x00000010
#define BIT_OX820_SYSCTRL_USBMPH_CTRL_OP_POL_B		4
#define MSK_OX820_SYSCTRL_USBMPH_CTRL_OP_POL_A		0x00000008
#define BIT_OX820_SYSCTRL_USBMPH_CTRL_OP_POL_A		3
#define MSK_OX820_SYSCTRL_USBMPH_CTRL_IP_POL_C		0x00000004
#define BIT_OX820_SYSCTRL_USBMPH_CTRL_IP_POL_C		2
#define MSK_OX820_SYSCTRL_USBMPH_CTRL_IP_POL_B		0x00000002
#define BIT_OX820_SYSCTRL_USBMPH_CTRL_IP_POL_B		1
#define MSK_OX820_SYSCTRL_USBMPH_CTRL_IP_POL_A		0x00000001
#define BIT_OX820_SYSCTRL_USBMPH_CTRL_IP_POL_A		0

#endif
