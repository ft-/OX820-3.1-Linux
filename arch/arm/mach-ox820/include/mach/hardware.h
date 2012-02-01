/*
 * arch/arm/mach-0x820/include/mach/hardware.h
 *
 * Copyright (C) 2009 Oxford Semiconductor Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __ASM_ARCH_HARDWARE_H
#define __ASM_ARCH_HARDWARE_H

#include <asm/page.h>
#include <asm/memory.h>
#include <asm/sizes.h>
#include <mach/vmalloc.h>
#include <mach/timex.h>

#define IO_ADDRESS(x)	(x)
#define __io_address(n)	((void __iomem *)IO_ADDRESS(n))

/* The base of virtual address mappings for hardware cores starts directly
 * after the end of the vmalloc mapping region
 */
#define OXNAS_HW_PA_TO_VA(x) (VMALLOC_END + (x))

/* Virtual address mapping of hardware core */
#define USBHOST_BASE			OXNAS_HW_PA_TO_VA(0x00200000)
#define ETHA_BASE				OXNAS_HW_PA_TO_VA(0x00400000)
#define MAC_BASE	(ETHA_BASE)
#define ETHB_BASE				OXNAS_HW_PA_TO_VA(0x00800000)
#define MAC_BASE_2	(ETHB_BASE)
#define USBDEV_BASE				OXNAS_HW_PA_TO_VA(0x00E00000)
#define STATIC_CS0_BASE			OXNAS_HW_PA_TO_VA(0x01000000)
#define STATIC_CS1_BASE			OXNAS_HW_PA_TO_VA(0x01400000)
#define STATIC_CONTROL_BASE		OXNAS_HW_PA_TO_VA(0x01C00000)
#define CIPHER_BASE				OXNAS_HW_PA_TO_VA(0x02000000)
#define GPIO_A_BASE				OXNAS_HW_PA_TO_VA(0x04000000)
#define GPIO_B_BASE				OXNAS_HW_PA_TO_VA(0x04100000)
#define UART_1_BASE				OXNAS_HW_PA_TO_VA(0x04200000)
#define UART_2_BASE				OXNAS_HW_PA_TO_VA(0x04300000)
#define RPSA_BASE				OXNAS_HW_PA_TO_VA(0x04400000)
#define RPSC_BASE				OXNAS_HW_PA_TO_VA(0x04500000)
#define FAN_MON_BASE			OXNAS_HW_PA_TO_VA(0x04600000)
#define DDR_REGS_BASE			OXNAS_HW_PA_TO_VA(0x04700000)
#define IRRX_BASE				OXNAS_HW_PA_TO_VA(0x04800000)
#define SATA_PHY_BASE			OXNAS_HW_PA_TO_VA(0x04900000)
#define PCIE_PHY				OXNAS_HW_PA_TO_VA(0x04A00000)
#define AHB_MON_BASE			OXNAS_HW_PA_TO_VA(0x04D00000)
#define SYS_CONTROL_BASE		OXNAS_HW_PA_TO_VA(0x04E00000)
#define SEC_CONTROL_BASE		OXNAS_HW_PA_TO_VA(0x04F00000)
#define SD_REG_BASE				OXNAS_HW_PA_TO_VA(0x05400000)
#define AUDIO_BASE				OXNAS_HW_PA_TO_VA(0x05500000)
#define DMA_BASE				OXNAS_HW_PA_TO_VA(0x05600000)
#define DMA_SG_BASE	(DMA_BASE + 0x10000)
#define CIPHER_REG_BASE			OXNAS_HW_PA_TO_VA(0x05700000)
#define SATA_REG_BASE			OXNAS_HW_PA_TO_VA(0x05900000)
#define COPRO_REGS_BASE			OXNAS_HW_PA_TO_VA(0x05B00000)
#define PERIPH_BASE				OXNAS_HW_PA_TO_VA(0x07000000)
#define PCIEA_DBI_BASE			OXNAS_HW_PA_TO_VA(0x07C00000)
#define PCIEA_ELBI_BASE			OXNAS_HW_PA_TO_VA(0x07D00000)
#define PCIEB_DBI_BASE			OXNAS_HW_PA_TO_VA(0x07E00000)
#define PCIEB_ELBI_BASE			OXNAS_HW_PA_TO_VA(0x07F00000)
#define PCIEA_CLIENT_BASE		OXNAS_HW_PA_TO_VA(0x08000000)
#define PCIEB_CLIENT_BASE		OXNAS_HW_PA_TO_VA(0x0c000000)

#define LEON_IMAGE_BASE       OXNAS_HW_PA_TO_VA(0x10000000)
#define SRAM_BASE             OXNAS_HW_PA_TO_VA(0x11000000)

/*
 * Location of flags and vectors in SRAM for controlling the booting of the
 * secondary ARM11 processors.
 */
#define HOLDINGPEN_CPU          (SYS_CONTROL_BASE + 0xc8)
#define HOLDINGPEN_LOCATION     (SYS_CONTROL_BASE + 0xc4)

/***************************************************************************/
/* Physical memory map */
//#define ROM_BASE_PA             0x40000000
#define USBHOST_BASE_PA         0x40200000
#define ETHA_BASE_PA            0x40400000
#define ETHB_BASE_PA            0x40800000
#define USBDEV_BASE_PA          0x40E00000
#define STATIC_CS0_BASE_PA      0x41000000
#define STATIC_CS1_BASE_PA      0x41400000
#define STATIC_CONTROL_BASE_PA  0x41C00000
#define CIPHER_BASE_PA		0x42000000
#define GPIO_A_BASE_PA          0x44000000
#define GPIO_B_BASE_PA          0x44100000
#define UART_1_BASE_PA          0x44200000
#define UART_2_BASE_PA          0x44300000
#define RPSA_BASE_PA            0x44400000
#define RPSC_BASE_PA            0x44500000
#define FAN_MON_BASE_PA		0x44600000
#define DDR_REGS_BASE_PA        0x44700000
#define IRRX_BASE_PA            0x44800000
#define SATA_PHY_BASE_PA        0x44900000
#define PCIE_PHY_PA             0x44a00000
#define AHB_MON_BASE_PA		0x44d00000
#define SYS_CONTROL_BASE_PA     0x44e00000
#define SEC_CONTROL_BASE_PA     0x44f00000
#define SD_REG_BASE_PA          0x45400000
#define AUDIO_BASE_PA           0x45500000
#define DMA_BASE_PA             0x45600000
#define CIPHER_REG_BASE_PA      0x45700000
#define SATA_REG_BASE_PA        0x45900000
#define COPRO_REGS_BASE_PA      0x45b00000
#define PERIPH_BASE_PA          0x47000000
#define PCIEA_DBI_BASE_PA       0x47c00000
#define PCIEA_ELBI_BASE_PA	0x47d00000
#define PCIEB_DBI_BASE_PA       0x47e00000
#define PCIEB_ELBI_BASE_PA	0x47f00000
#define PCIEA_CLIENT_BASE_PA	0x48000000
#define PCIEB_CLIENT_BASE_PA	0x4c000000

/* System clock frequencies */
#ifdef CONFIG_ARCH_OXNAS_FPGA
/* FPGA CPU clock is entirely independent of rest of SoC */
#define NOMINAL_ARMCLK (CONFIG_OXNAS_CORE_CLK)
#else // CONFIG_ARCH_OXNAS_FPGA
/* ASIC CPU clock is derived from SoC master clock */
#define NOMINAL_ARMCLK (CONFIG_NOMINAL_PLL400_FREQ / 2)
#endif // CONFIG_ARCH_OXNAS_FPGA

#define NOMINAL_SYSCLK (CONFIG_NOMINAL_PLL400_FREQ / 4)

/* MPCore specific registers */
#define OX820_ARM11MP_SCU_BASE       (PERIPH_BASE | 0x0000)
#define OX820_GIC_CPU_BASE_ADDR      (PERIPH_BASE | 0x0100)
#define OX820_GIC_CPUN_BASE_ADDR(n)  (PERIPH_BASE + 0x0200 + ((n) * 0x100))
#define OX820_TWD_BASE               (PERIPH_BASE | 0x0600)
#define OX820_TWD_CPU0_BASE          (PERIPH_BASE | 0x0700)
#define OX820_TWD_CPU1_BASE          (PERIPH_BASE | 0x0800)
#define OX820_TWD_CPU2_BASE          (PERIPH_BASE | 0x0900)
#define OX820_TWD_CPU3_BASE          (PERIPH_BASE | 0x0A00)
#define OX820_GIC_DIST_BASE_ADDR     (PERIPH_BASE | 0x1000)

#define OX820_ARM11MP_TWD_SIZE 0x100


#include <mach/hardware-legacy.h>

#endif // __ASM_ARCH_HARDWARE_H
