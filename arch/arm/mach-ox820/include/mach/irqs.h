/*
 * arch/arm/mach-0x820/include/mach/irqs.h
 *
 * Copyright (C) 2009 Oxford Semiconductor Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __ASM_ARCH_IRQS_H
#define __ASM_ARCH_IRQS_H

/**************************************/
/* ARM GIC */
#define OX820_ARM_GIC_IRQ_START             0
/* these IRQs are recommended for ARM drivers due to the linkage to the GIC */
#define OX820_ARM_GIC_IRQ_LOCAL_TIMER       (OX820_ARM_GIC_IRQ_START + 29)
#define OX820_ARM_GIC_IRQ_LOCAL_WATCHDOG    (OX820_ARM_GIC_IRQ_START + 30)

#define OX820_ARM_GIC_IRQ_RPSC_FIQ          (OX820_ARM_GIC_IRQ_START + 34)
#define OX820_ARM_GIC_IRQ_RPSC_IRQ          (OX820_ARM_GIC_IRQ_START + 35)
#define OX820_ARM_GIC_IRQ_RPSA_FIQ          (OX820_ARM_GIC_IRQ_START + 36)
#define OX820_ARM_GIC_IRQ_RPSA_IRQ          (OX820_ARM_GIC_IRQ_START + 37)
#define OX820_ARM_GIC_IRQ_IRRX              (OX820_ARM_GIC_IRQ_START + 38)
#define OX820_ARM_GIC_IRQ_USBHOST           (OX820_ARM_GIC_IRQ_START + 39)
#define OX820_ARM_GIC_IRQ_GMAC_A            (OX820_ARM_GIC_IRQ_START + 40)
#define OX820_ARM_GIC_IRQ_GMAC_B            (OX820_ARM_GIC_IRQ_START + 41)
#define OX820_ARM_GIC_IRQ_SEM_A             (OX820_ARM_GIC_IRQ_START + 42)
#define OX820_ARM_GIC_IRQ_SEM_B             (OX820_ARM_GIC_IRQ_START + 43)
#define OX820_ARM_GIC_IRQ_SEM_C             (OX820_ARM_GIC_IRQ_START + 44)
#define OX820_ARM_GIC_IRQ_SGDMA_CH0         (OX820_ARM_GIC_IRQ_START + 45)
#define OX820_ARM_GIC_IRQ_SGDMA_CH1         (OX820_ARM_GIC_IRQ_START + 46)
#define OX820_ARM_GIC_IRQ_SGDMA_CH2         (OX820_ARM_GIC_IRQ_START + 47)
#define OX820_ARM_GIC_IRQ_SGDMA_CH3         (OX820_ARM_GIC_IRQ_START + 48)
#define OX820_ARM_GIC_IRQ_GMAC_A_PMT        (OX820_ARM_GIC_IRQ_START + 49)
#define OX820_ARM_GIC_IRQ_SATA              (OX820_ARM_GIC_IRQ_START + 50)
#define OX820_ARM_GIC_IRQ_PCIE_A            (OX820_ARM_GIC_IRQ_START + 51)
#define OX820_ARM_GIC_IRQ_PCIE_B            (OX820_ARM_GIC_IRQ_START + 52)
#define OX820_ARM_GIC_IRQ_GPIO_A            (OX820_ARM_GIC_IRQ_START + 53)
#define OX820_ARM_GIC_IRQ_GPIO_B            (OX820_ARM_GIC_IRQ_START + 54)
#define OX820_ARM_GIC_IRQ_UART_1            (OX820_ARM_GIC_IRQ_START + 55)
#define OX820_ARM_GIC_IRQ_UART_2            (OX820_ARM_GIC_IRQ_START + 56)
#define OX820_ARM_GIC_IRQ_AUDIO             (OX820_ARM_GIC_IRQ_START + 57)
#define OX820_ARM_GIC_IRQ_AUDIO_ERROR       (OX820_ARM_GIC_IRQ_START + 58)
#define OX820_ARM_GIC_IRQ_VIDEO_OUTPUT      (OX820_ARM_GIC_IRQ_START + 59)
#define OX820_ARM_GIC_IRQ_GMAC_B_PMT        (OX820_ARM_GIC_IRQ_START + 60)
#define OX820_ARM_GIC_IRQ_SD                (OX820_ARM_GIC_IRQ_START + 61)
#define OX820_ARM_GIC_IRQ_USBDEV            (OX820_ARM_GIC_IRQ_START + 62)

/**************************************/
/* RPSA */
#define OX820_RPSA_IRQ_START                64
/* do not use this lines when they are available on ARM GIC */
#define OX820_RPSA_IRQ_FIQ                  (OX820_RPSA_IRQ_START + 0)
#define OX820_RPSA_IRQ_SWIRQ                (OX820_RPSA_IRQ_START + 1)
#define OX820_RPSA_IRQ_ARM_COMMRX           (OX820_RPSA_IRQ_START + 2)
#define OX820_RPSA_IRQ_ARM_COMMTX           (OX820_RPSA_IRQ_START + 3)
#define OX820_RPSA_IRQ_RPSA_TIMER1          (OX820_RPSA_IRQ_START + 4)
#define OX820_RPSA_IRQ_RPSA_TIMER2          (OX820_RPSA_IRQ_START + 5)
#define OX820_RPSA_IRQ_IRRX                 (OX820_RPSA_IRQ_START + 6)
#define OX820_RPSA_IRQ_USBHOST              (OX820_RPSA_IRQ_START + 7)
#define OX820_RPSA_IRQ_GMAC_A               (OX820_RPSA_IRQ_START + 8)
#define OX820_RPSA_IRQ_GMAC_B               (OX820_RPSA_IRQ_START + 9)
#define OX820_RPSA_IRQ_SEM_A                (OX820_RPSA_IRQ_START + 10)
#define OX820_RPSA_IRQ_SEM_B                (OX820_RPSA_IRQ_START + 11)
#define OX820_RPSA_IRQ_SEM_C                (OX820_RPSA_IRQ_START + 12)
#define OX820_RPSA_IRQ_SGDMA_CH0            (OX820_RPSA_IRQ_START + 13)
#define OX820_RPSA_IRQ_SGDMA_CH1            (OX820_RPSA_IRQ_START + 14)
#define OX820_RPSA_IRQ_SGDMA_CH2            (OX820_RPSA_IRQ_START + 15)
#define OX820_RPSA_IRQ_SGDMA_CH3            (OX820_RPSA_IRQ_START + 16)
#define OX820_RPSA_IRQ_GMAC_A_PMT           (OX820_RPSA_IRQ_START + 17)
#define OX820_RPSA_IRQ_SATA                 (OX820_RPSA_IRQ_START + 18)
#define OX820_RPSA_IRQ_PCIE_A               (OX820_RPSA_IRQ_START + 19)
#define OX820_RPSA_IRQ_PCIE_B               (OX820_RPSA_IRQ_START + 20)
#define OX820_RPSA_IRQ_GPIO_A               (OX820_RPSA_IRQ_START + 21)
#define OX820_RPSA_IRQ_GPIO_B               (OX820_RPSA_IRQ_START + 22)
#define OX820_RPSA_IRQ_UART_1               (OX820_RPSA_IRQ_START + 23)
#define OX820_RPSA_IRQ_UART_2               (OX820_RPSA_IRQ_START + 24)
#define OX820_RPSA_IRQ_AUDIO                (OX820_RPSA_IRQ_START + 25)
#define OX820_RPSA_IRQ_AUDIO_ERROR          (OX820_RPSA_IRQ_START + 26)
#define OX820_RPSA_IRQ_VIDEO_OUTPUT         (OX820_RPSA_IRQ_START + 27)
#define OX820_RPSA_IRQ_GMAC_B_PMT           (OX820_RPSA_IRQ_START + 28)
#define OX820_RPSA_IRQ_SD                   (OX820_RPSA_IRQ_START + 29)
#define OX820_RPSA_IRQ_USBDEV               (OX820_RPSA_IRQ_START + 30)

/**************************************/
/* RPSC */
#define OX820_RPSC_IRQ_START                96
/* these lines are normally used within Leon2 code, 
 * so do not use when Leon2 is in use.
 */
#define OX820_RPSC_IRQ_FIQ                  (OX820_RPSC_IRQ_START + 0)
#define OX820_RPSC_IRQ_SWIRQ                (OX820_RPSC_IRQ_START + 1)
#define OX820_RPSC_IRQ_ARM_COMMRX           (OX820_RPSC_IRQ_START + 2)
#define OX820_RPSC_IRQ_ARM_COMMTX           (OX820_RPSC_IRQ_START + 3)
#define OX820_RPSC_IRQ_RPSC_TIMER1          (OX820_RPSC_IRQ_START + 4)
#define OX820_RPSC_IRQ_RPSC_TIMER2          (OX820_RPSC_IRQ_START + 5)
#define OX820_RPSC_IRQ_IRRX                 (OX820_RPSC_IRQ_START + 6)
#define OX820_RPSC_IRQ_USBHOST              (OX820_RPSC_IRQ_START + 7)
#define OX820_RPSC_IRQ_GMAC_A               (OX820_RPSC_IRQ_START + 8)
#define OX820_RPSC_IRQ_GMAC_B               (OX820_RPSC_IRQ_START + 9)
#define OX820_RPSC_IRQ_SEM_A                (OX820_RPSC_IRQ_START + 10)
#define OX820_RPSC_IRQ_SEM_B                (OX820_RPSC_IRQ_START + 11)
#define OX820_RPSC_IRQ_SEM_C                (OX820_RPSC_IRQ_START + 12)
#define OX820_RPSC_IRQ_SGDMA_CH0            (OX820_RPSC_IRQ_START + 13)
#define OX820_RPSC_IRQ_SGDMA_CH1            (OX820_RPSC_IRQ_START + 14)
#define OX820_RPSC_IRQ_SGDMA_CH2            (OX820_RPSC_IRQ_START + 15)
#define OX820_RPSC_IRQ_SGDMA_CH3            (OX820_RPSC_IRQ_START + 16)
#define OX820_RPSC_IRQ_GMAC_A_PMT           (OX820_RPSC_IRQ_START + 17)
#define OX820_RPSC_IRQ_SATA                 (OX820_RPSC_IRQ_START + 18)
#define OX820_RPSC_IRQ_PCIE_A               (OX820_RPSC_IRQ_START + 19)
#define OX820_RPSC_IRQ_PCIE_B               (OX820_RPSC_IRQ_START + 20)
#define OX820_RPSC_IRQ_GPIO_A               (OX820_RPSC_IRQ_START + 21)
#define OX820_RPSC_IRQ_GPIO_B               (OX820_RPSC_IRQ_START + 22)
#define OX820_RPSC_IRQ_UART_1               (OX820_RPSC_IRQ_START + 23)
#define OX820_RPSC_IRQ_UART_2               (OX820_RPSC_IRQ_START + 24)
#define OX820_RPSC_IRQ_AUDIO                (OX820_RPSC_IRQ_START + 25)
#define OX820_RPSC_IRQ_AUDIO_ERROR          (OX820_RPSC_IRQ_START + 26)
#define OX820_RPSC_IRQ_VIDEO_OUTPUT         (OX820_RPSC_IRQ_START + 27)
#define OX820_RPSC_IRQ_GMAC_B_PMT           (OX820_RPSC_IRQ_START + 28)
#define OX820_RPSC_IRQ_SD                   (OX820_RPSC_IRQ_START + 29)
#define OX820_RPSC_IRQ_USBDEV               (OX820_RPSC_IRQ_START + 30)

/**************************************/
/* GPIO-A and B */
#define OX820_GPIO_IRQ_START                128
#define OX820_GPIO_IRQ_NR                   50

#define NR_IRQS (OX820_GPIO_IRQ_START + OX820_GPIO_IRQ_NR)

#if 0
/* Definitions for the RPS core irq controller */
#define OX820_RPS_IRQ_START 64
#define NR_RPS_IRQS 32

#define RPS_FIQ_INTERRUPT			(OX820_RPS_IRQ_START +  0)
#define RPS_SOFTWARE_INTERRUPT		(OX820_RPS_IRQ_START +  1)
#define RPS_COMMRX_INTERRUPT		(OX820_RPS_IRQ_START +  2)
#define RPS_COMMTX_INTERRUPT		(OX820_RPS_IRQ_START +  3)
#define RPS_TIMER_1_INTERRUPT		(OX820_RPS_IRQ_START +  4)
#define RPS_TIMER_2_INTERRUPT		(OX820_RPS_IRQ_START +  5)
#define RPS_IRRX_INTERRUPT			(OX820_RPS_IRQ_START +  6)
#define RPS_USBHOST_INTERRUPT		(OX820_RPS_IRQ_START +  7)
#define RPS_MAC_INTERRUPT			(OX820_RPS_IRQ_START +  8)
#define RPS_MAC_2_INTERRUPT			(OX820_RPS_IRQ_START +  9)
#define RPS_SEM_A_INTERRUPT 		(OX820_RPS_IRQ_START + 10)
#define RPS_SEM_B_INTERRUPT 		(OX820_RPS_IRQ_START + 11)
#define RPS_SEM_C_INTERRUPT			(OX820_RPS_IRQ_START + 12)
#define RPS_DMA_INTERRUPT_0			(OX820_RPS_IRQ_START + 13)
#define RPS_DMA_INTERRUPT_1			(OX820_RPS_IRQ_START + 14)
#define RPS_DMA_INTERRUPT_2			(OX820_RPS_IRQ_START + 15)
#define RPS_DMA_INTERRUPT_3			(OX820_RPS_IRQ_START + 16)
#define RPS_DMA_INTERRUPT_4			(OX820_RPS_IRQ_START + 17)
#define RPS_SATA_INTERRUPT			(OX820_RPS_IRQ_START + 18)
#define RPS_PCIEA_INTERRUPT			(OX820_RPS_IRQ_START + 19)
#define RPS_PCIEB_INTERRUPT			(OX820_RPS_IRQ_START + 20)
#define RPS_GPIOA_INTERRUPT			(OX820_RPS_IRQ_START + 21)
#define RPS_GPIOB_INTERRUPT			(OX820_RPS_IRQ_START + 22)
#define RPS_UART_1_INTERRUPT		(OX820_RPS_IRQ_START + 23)
#define RPS_UART_2_INTERRUPT		(OX820_RPS_IRQ_START + 24)
#define RPS_AUDIO_DATA_INTERRUPT	(OX820_RPS_IRQ_START + 25)
#define RPS_AUDIO_ERR_INTERRUPT		(OX820_RPS_IRQ_START + 26)
#define RPS_CIPHERD_INTERRUPT		(OX820_RPS_IRQ_START + 27)
#define RPS_CIPHERE_INTERRUPT		(OX820_RPS_IRQ_START + 28)
#define RPS_SD_INTERRUPT			(OX820_RPS_IRQ_START + 29)
#define RPS_USBDEV_INTERRUPT		(OX820_RPS_IRQ_START + 30)

#define OX820_GIC_IRQ_START  32
#define NR_GIC_IRQS (OX820_GIC_IRQ_START + 32) /* looks weird to me */

/* The per CPU timer interrupt */
#define IRQ_LOCALTIMER            (29)

#define RPSC_FIQ_INTERRUPT 			(OX820_GIC_IRQ_START +  2)
#define RPSC_IRQ_INTERRUPT 			(OX820_GIC_IRQ_START +  3)
#define RPSA_FIQ_INTERRUPT 			(OX820_GIC_IRQ_START +  4)
#define RPSA_IRQ_INTERRUPT 			(OX820_GIC_IRQ_START +  5)
#define IRRX_INTERRUPT				(OX820_GIC_IRQ_START +  6)
#define USBHOST_INTERRUPT			(OX820_GIC_IRQ_START +  7)
#define MAC_INTERRUPT				(OX820_GIC_IRQ_START +  8)
#define MAC_2_INTERRUPT				(OX820_GIC_IRQ_START +  9)
#define SEM_A_INTERRUPT 			(OX820_GIC_IRQ_START + 10)
#define SEM_B_INTERRUPT 			(OX820_GIC_IRQ_START + 11)
#define SEM_C_INTERRUPT 			(OX820_GIC_IRQ_START + 12)
#define DMA_INTERRUPT_0 			(OX820_GIC_IRQ_START + 13)
#define DMA_INTERRUPT_1 			(OX820_GIC_IRQ_START + 14)
#define DMA_INTERRUPT_2 			(OX820_GIC_IRQ_START + 15)
#define DMA_INTERRUPT_3 			(OX820_GIC_IRQ_START + 16)
#define DMA_INTERRUPT_4				(OX820_GIC_IRQ_START + 17)
#define SATA_INTERRUPT				(OX820_GIC_IRQ_START + 18)
#define PCIEA_INTERRUPT				(OX820_GIC_IRQ_START + 19)
#define PCIEB_INTERRUPT				(OX820_GIC_IRQ_START + 20)
#define GPIOA_INTERRUPT				(OX820_GIC_IRQ_START + 21)
#define GPIOB_INTERRUPT				(OX820_GIC_IRQ_START + 22)
#define UART_1_INTERRUPT 			(OX820_GIC_IRQ_START + 23)
#define UART_2_INTERRUPT 			(OX820_GIC_IRQ_START + 24)
#define AUDIO_DATA_INTERRUPT		(OX820_GIC_IRQ_START + 25)
#define AUDIO_ERR_INTERRUPT			(OX820_GIC_IRQ_START + 26)
#define CIPHERD_INTERRUPT			(OX820_GIC_IRQ_START + 27)
#define CIPHERE_INTERRUPT			(OX820_GIC_IRQ_START + 28)
#define SD_INTERRUPT				(OX820_GIC_IRQ_START + 29)
#define USBDEV_INTERRUPT			(OX820_GIC_IRQ_START + 30)

#define OX820_GPIO_IRQ_START 96
#define NR_GPIO_IRQS 50

/* Definitions for the ARM11's GIC IRQ controller */ 
#define NR_IRQS (NR_GPIO_IRQS + NR_GIC_IRQS + NR_RPS_IRQS) /* 96 RPS + 50 for GPIO stuff */
#endif

#endif // __ASM_ARCH_IRQ_H
