/*
 * arch/arm/mach-0x820/include/mach/system.h
 *
 * Copyright (C) 2009 Oxford Semiconductor Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __ASM_ARCH_SYSTEM_H
#define __ASM_ARCH_SYSTEM_H

#include <mach/hardware.h>
#include <linux/io.h>
#include <mach/hw/sysctrl.h>
#include <mach/hw/secctrl.h>

static inline void arch_idle(void)
{
    /*
     * This should do all the clock switching
     * and wait for interrupt tricks
     */
    cpu_do_idle();
}

static inline void arch_reset(char mode, const char* command)
{
    struct ox820_sysctrl_registers_t* sysctrl = (struct ox820_sysctrl_registers_t*) SYS_CONTROL_BASE;
    struct ox820_secctrl_registers_t* secctrl = (struct ox820_secctrl_registers_t*) SEC_CONTROL_BASE;
    
    // Assert reset to cores as per power on defaults
	// Don't touch the DDR interface as things will come to an impromptu stop
	// NB Possibly should be asserting reset for PLLB, but there are timing
	//    concerns here according to the docs
    sysctrl->rsten_set_ctrl = MSK_OX820_SYSCTRL_RSTEN_LEON |
			MSK_OX820_SYSCTRL_RSTEN_USBMPH |
			MSK_OX820_SYSCTRL_RSTEN_USBPHYA |
			MSK_OX820_SYSCTRL_RSTEN_ETHA |
			MSK_OX820_SYSCTRL_RSTEN_PCIEA |
			MSK_OX820_SYSCTRL_RSTEN_DMA_SGDMA |
			MSK_OX820_SYSCTRL_RSTEN_CIPHER |
			MSK_OX820_SYSCTRL_RSTEN_SATA |
			MSK_OX820_SYSCTRL_RSTEN_SATALINK |
			MSK_OX820_SYSCTRL_RSTEN_SATAPHY |
			MSK_OX820_SYSCTRL_RSTEN_PCIEPHY |
			MSK_OX820_SYSCTRL_RSTEN_STATIC |
			MSK_OX820_SYSCTRL_RSTEN_UARTA |
			MSK_OX820_SYSCTRL_RSTEN_UARTB |
			MSK_OX820_SYSCTRL_RSTEN_FAN_IRRX |
			MSK_OX820_SYSCTRL_RSTEN_AUDIO |
			MSK_OX820_SYSCTRL_RSTEN_SD |
			MSK_OX820_SYSCTRL_RSTEN_ETHB |
			MSK_OX820_SYSCTRL_RSTEN_PCIEB |
			MSK_OX820_SYSCTRL_RSTEN_VIDEO |
			MSK_OX820_SYSCTRL_RSTEN_USBPHYB |
			MSK_OX820_SYSCTRL_RSTEN_USBDEV;

    // Release reset to cores as per power on defaults
    sysctrl->rsten_clr_ctrl = MSK_OX820_SYSCTRL_RSTEN_GPIO;

    // Disable clocks to cores as per power-on defaults - must leave DDR
	// related clocks enabled otherwise we'll stop rather abruptly.
    sysctrl->cken_clr_ctrl = MSK_OX820_SYSCTRL_CKEN_LEON |
			MSK_OX820_SYSCTRL_CKEN_DMA_SGDMA |
			MSK_OX820_SYSCTRL_CKEN_CIPHER |
			MSK_OX820_SYSCTRL_CKEN_SD |
			MSK_OX820_SYSCTRL_CKEN_SATA |
			MSK_OX820_SYSCTRL_CKEN_AUDIO |
			MSK_OX820_SYSCTRL_CKEN_USBMPH |
			MSK_OX820_SYSCTRL_CKEN_ETHA |
			MSK_OX820_SYSCTRL_CKEN_PCIEA |
			MSK_OX820_SYSCTRL_CKEN_STATIC |
			MSK_OX820_SYSCTRL_CKEN_ETHB |
			MSK_OX820_SYSCTRL_CKEN_PCIEB |
			MSK_OX820_SYSCTRL_CKEN_REF600 |
			MSK_OX820_SYSCTRL_CKEN_USBDEV;

    // Enable clocks to cores as per power-on defaults

    // Set sys-control pin mux'ing as per power-on defaults
    sysctrl->mfa_secsel_ctrl = 0;
    sysctrl->mfa_tersel_ctrl = 0;
    sysctrl->mfa_quatsel_ctrl = 0;
    sysctrl->mfa_debugsel_ctrl = 0;
    sysctrl->mfa_altsel_ctrl = 0;
    sysctrl->mfa_pullup_ctrl = 0;

    secctrl->mfb_secsel_ctrl = 0;
    secctrl->mfb_tersel_ctrl = 0;
    secctrl->mfb_quatsel_ctrl = 0;
    secctrl->mfb_debugsel_ctrl = 0;
    secctrl->mfb_altsel_ctrl = 0;
    secctrl->mfb_pullup_ctrl = 0;

    // No need to save any state, as the ROM loader can determine whether reset
    // is due to power cycling or programatic action, just hit the (self-
    // clearing) CPU reset bit of the block reset register
    sysctrl->rsten_set_ctrl = MSK_OX820_SYSCTRL_RSTEN_ARM_SCU |
			MSK_OX820_SYSCTRL_RSTEN_ARM_CPU0 |
			MSK_OX820_SYSCTRL_RSTEN_ARM_CPU1;
}

#endif // __ASM_ARCH_SYSTEM_H

