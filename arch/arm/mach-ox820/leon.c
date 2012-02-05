/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/spinlock.h>
#include <mach/leon.h>
#include <mach/hw/leon.h>
#include <mach/hw/sysctrl.h>
#include <mach/hw/secctrl.h>
#include <mach/hw/rpsc.h>
#include <mach/hardware.h>

static DEFINE_SPINLOCK(ox820_leon_lock);
static struct platform_device* ox820_leon_locked_by = NULL;
static struct ox820_sysctrl_registers_t* const regs_sysctrl = (struct ox820_sysctrl_registers_t*) SYS_CONTROL_BASE;
static struct ox820_secctrl_registers_t* const regs_secctrl = (struct ox820_secctrl_registers_t*) SEC_CONTROL_BASE;

int ox820_request_leon(struct platform_device* dev)
{
	unsigned long flags;
	int ret = -EBUSY;

	spin_lock_irqsave(&ox820_leon_lock, flags);

	if(NULL == ox820_leon_locked_by) {
		ret = 0;
		ox820_leon_locked_by = dev;
	}
	spin_unlock_irqrestore(&ox820_leon_lock, flags);

	return ret;
}

int ox820_release_leon(struct platform_device* dev)
{
	unsigned long flags;
	int ret = -EINVAL;

	spin_lock_irqsave(&ox820_leon_lock, flags);

	if(dev == ox820_leon_locked_by) {
		ret = 0;
		ox820_leon_locked_by = NULL;
	}
	spin_unlock_irqrestore(&ox820_leon_lock, flags);

	return ret;
}

int ox820_set_clock(enum ox820_leon_clockmode_t clkmode)
{
	unsigned long flags;
	int ret = -EPERM;

	spin_lock_irqsave(&ox820_leon_lock, flags);

	if(!(regs_sysctrl->cken_stat & MSK_OX820_SYSCTRL_CKEN_LEON)) {
		ret = 0;
		switch(clkmode) {
			case OX820_LEON_CLOCKMODE_DIV_4:
				regs_secctrl->leon_ctrl &= (~MSK_OX820_SECCTRL_LEON_CTRL_DOUBLE_CLK);
				break;
			case OX820_LEON_CLOCKMODE_DIV_2:
				regs_secctrl->leon_ctrl |= MSK_OX820_SECCTRL_LEON_CTRL_DOUBLE_CLK;
				break;
		}
		/* Leon clock is now configured */
	}
	spin_unlock_irqrestore(&ox820_leon_lock, flags);

	return ret;
}

int ox820_start_leon(dma_addr_t startaddr)
{
	unsigned long flags;
	int ret = -EBUSY;

	spin_lock_irqsave(&ox820_leon_lock, flags);

	if(!(regs_sysctrl->cken_stat & MSK_OX820_SYSCTRL_CKEN_LEON)) {
		ret = 0;
		regs_secctrl->leon_ctrl = (startaddr & (MSK_OX820_SECCTRL_LEON_CTRL_START_ADDR)) |
					(regs_secctrl->leon_ctrl & (~MSK_OX820_SECCTRL_LEON_CTRL_START_ADDR));
		regs_sysctrl->cken_set_ctrl = MSK_OX820_SYSCTRL_CKEN_LEON;
		regs_sysctrl->rsten_clr_ctrl = MSK_OX820_SYSCTRL_RSTEN_LEON;
		/* Leon is now started at the provided physical start address */
	}
	spin_unlock_irqrestore(&ox820_leon_lock, flags);

	return ret;
}

int ox820_stop_leon(void)
{
	unsigned long flags;
	int ret = -EPERM;

	spin_lock_irqsave(&ox820_leon_lock, flags);

	if(regs_sysctrl->cken_stat & MSK_OX820_SYSCTRL_CKEN_LEON) {
		ret = 0;
		regs_sysctrl->rsten_set_ctrl = MSK_OX820_SYSCTRL_RSTEN_LEON;
		regs_sysctrl->cken_clr_ctrl = MSK_OX820_SYSCTRL_CKEN_LEON;
		/* Leon is now stopped */
	}
	spin_unlock_irqrestore(&ox820_leon_lock, flags);

	return ret;
}

int ox820_is_leon_running(void)
{
	return (regs_sysctrl->cken_stat & MSK_OX820_SYSCTRL_CKEN_LEON) != 0;
}

int ox820_leon_trigger_irq2(void)
{
	unsigned long flags;
	int ret = -EPERM;

	spin_lock_irqsave(&ox820_leon_lock, flags);

	if(regs_sysctrl->cken_stat & MSK_OX820_SYSCTRL_CKEN_LEON) {
		ret = 0;
		regs_secctrl->leon_ctrl = 1;
	}
	spin_unlock_irqrestore(&ox820_leon_lock, flags);

	return ret;
}

int ox820_leon_trigger_rps_softirq(void)
{
	unsigned long flags;
	int ret = -EPERM;
	struct ox820_rpsc_registers_t* rpsc = (struct ox820_rpsc_registers_t*) RPSC_BASE;

	spin_lock_irqsave(&ox820_leon_lock, flags);

	if(regs_sysctrl->cken_stat & MSK_OX820_SYSCTRL_CKEN_LEON) {
		ret = 0;
		rpsc->software_irq = 1;
	}
	spin_unlock_irqrestore(&ox820_leon_lock, flags);

	return ret;
}
