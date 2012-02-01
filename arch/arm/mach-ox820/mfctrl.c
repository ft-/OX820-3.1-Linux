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
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/spinlock.h>
#include <mach/mfctrl.h>
#include <mach/hw/sysctrl.h>
#include <mach/hw/secctrl.h>
#include <mach/hw/gpio.h>
#include <mach/hardware.h>
    
static DEFINE_SPINLOCK(ox820_mf_lock);

void ox820_mf_select(enum ox820_mfctrl_t function)
{
	struct ox820_sysctrl_registers_t* sysctrl = (struct ox820_sysctrl_registers_t*) SYS_CONTROL_BASE;
	struct ox820_secctrl_registers_t* secctrl = (struct ox820_secctrl_registers_t*) SEC_CONTROL_BASE;
	u32 mask = 1 << (function % 32);
	unsigned long flags;
    
	if(function % 1000 > 49) {
		return;
	}
    
	spin_lock_irqsave(&ox820_mf_lock, flags);
    
	switch(function / 1000) {
		case 0: /* GPIO */
			/* switch MF bit to input first */
			ox820_mf_set_gpio_direction(function, OX820_DIR_INPUT);
    
			if(function & 32) {
				secctrl->mfb_secsel_ctrl &= (~mask);
				secctrl->mfb_tersel_ctrl &= (~mask);
				secctrl->mfb_quatsel_ctrl &= (~mask);
				secctrl->mfb_debugsel_ctrl &= (~mask);
				secctrl->mfb_altsel_ctrl &= (~mask);
			} else {
				sysctrl->mfa_secsel_ctrl &= (~mask);
				sysctrl->mfa_tersel_ctrl &= (~mask);
				sysctrl->mfa_quatsel_ctrl &= (~mask);
				sysctrl->mfa_debugsel_ctrl &= (~mask);
				sysctrl->mfa_altsel_ctrl &= (~mask);
			}
			break;
        
		case 1: /* Alternate */
			if(function & 32) {
				secctrl->mfb_secsel_ctrl &= (~mask);
				secctrl->mfb_tersel_ctrl &= (~mask);
				secctrl->mfb_quatsel_ctrl &= (~mask);
				secctrl->mfb_debugsel_ctrl &= (~mask);
				secctrl->mfb_altsel_ctrl |= (mask);
			} else {
				sysctrl->mfa_secsel_ctrl &= (~mask);
				sysctrl->mfa_tersel_ctrl &= (~mask);
				sysctrl->mfa_quatsel_ctrl &= (~mask);
				sysctrl->mfa_debugsel_ctrl &= (~mask);
				sysctrl->mfa_altsel_ctrl |= (mask);
			}
			break;
        
		case 2: /* Secondary */
			if(function & 32) {
				secctrl->mfb_altsel_ctrl &= (~mask);
				secctrl->mfb_tersel_ctrl &= (~mask);
				secctrl->mfb_quatsel_ctrl &= (~mask);
				secctrl->mfb_debugsel_ctrl &= (~mask);
				secctrl->mfb_secsel_ctrl |= (mask);
			} else {
				sysctrl->mfa_altsel_ctrl &= (~mask);
				sysctrl->mfa_tersel_ctrl &= (~mask);
				sysctrl->mfa_quatsel_ctrl &= (~mask);
				sysctrl->mfa_debugsel_ctrl &= (~mask);
				sysctrl->mfa_secsel_ctrl |= (mask);
			}
			break;
        
		case 3: /* Tertiary */
			if(function & 32) {
				secctrl->mfb_altsel_ctrl &= (~mask);
				secctrl->mfb_secsel_ctrl &= (~mask);
				secctrl->mfb_quatsel_ctrl &= (~mask);
				secctrl->mfb_debugsel_ctrl &= (~mask);
				secctrl->mfb_tersel_ctrl |= (mask);
			} else {
				sysctrl->mfa_altsel_ctrl &= (~mask);
				sysctrl->mfa_secsel_ctrl &= (~mask);
				sysctrl->mfa_quatsel_ctrl &= (~mask);
				sysctrl->mfa_debugsel_ctrl &= (~mask);
				sysctrl->mfa_tersel_ctrl |= (mask);
			}
			break;
        
		case 4: /* Quaterniary */
			if(function & 32) {
				secctrl->mfb_altsel_ctrl &= (~mask);
				secctrl->mfb_secsel_ctrl &= (~mask);
				secctrl->mfb_tersel_ctrl &= (~mask);
				secctrl->mfb_debugsel_ctrl &= (~mask);
				secctrl->mfb_quatsel_ctrl |= (mask);
			} else {
				sysctrl->mfa_altsel_ctrl &= (~mask);
				sysctrl->mfa_secsel_ctrl &= (~mask);
				sysctrl->mfa_tersel_ctrl &= (~mask);
				sysctrl->mfa_debugsel_ctrl &= (~mask);
				sysctrl->mfa_quatsel_ctrl |= (mask);
			}
			break;
        
		case 5: /* Debug */
			if(function & 32) {
				secctrl->mfb_altsel_ctrl &= (~mask);
				secctrl->mfb_secsel_ctrl &= (~mask);
				secctrl->mfb_tersel_ctrl &= (~mask);
				secctrl->mfb_quatsel_ctrl &= (~mask);
				secctrl->mfb_debugsel_ctrl |= (mask);
			} else {
				sysctrl->mfa_altsel_ctrl &= (~mask);
				sysctrl->mfa_secsel_ctrl &= (~mask);
				sysctrl->mfa_tersel_ctrl &= (~mask);
				sysctrl->mfa_quatsel_ctrl &= (~mask);
				sysctrl->mfa_debugsel_ctrl |= (mask);
			}
			break;
	}
	wmb();
    
	spin_unlock_irqrestore(&ox820_mf_lock, flags);
}

EXPORT_SYMBOL(ox820_mf_select);

void ox820_mf_set_gpio_direction(enum ox820_mfctrl_t function, enum ox820_mfctrl_direction_t direction)
{
	u32 mask = 1 << (function % 32);
    
	if(function % 1000 > 49) {
		return;
	}
    
	if(function & 32) {
		struct ox820_gpio_registers_t* gpioreg = (struct ox820_gpio_registers_t*) GPIO_B_BASE;
        	if(OX820_DIR_OUTPUT == direction) {
        		gpioreg->output_enable_set = mask;
        	} else {
        		gpioreg->output_enable_clear = mask;
        	}
	} else {
		struct ox820_gpio_registers_t* gpioreg = (struct ox820_gpio_registers_t*) GPIO_A_BASE;
		if(OX820_DIR_OUTPUT == direction) {
			gpioreg->output_enable_set = mask;
		} else {
			gpioreg->output_enable_clear = mask;
		}
	}
}

EXPORT_SYMBOL(ox820_mf_set_gpio_direction);

void ox820_mf_select_gpio(u32 gpionr)
{
	struct ox820_sysctrl_registers_t* sysctrl = (struct ox820_sysctrl_registers_t*) SYS_CONTROL_BASE;
	struct ox820_secctrl_registers_t* secctrl = (struct ox820_secctrl_registers_t*) SEC_CONTROL_BASE;
	u32 mask = 1 << (gpionr % 32);
	unsigned long flags;
    
	if(gpionr % 1000 > 49) {
		return;
	}
    
	spin_lock_irqsave(&ox820_mf_lock, flags);
	if(gpionr & 32) {
		secctrl->mfb_secsel_ctrl &= (~mask);
		secctrl->mfb_tersel_ctrl &= (~mask);
		secctrl->mfb_quatsel_ctrl &= (~mask);
		secctrl->mfb_debugsel_ctrl &= (~mask);
		secctrl->mfb_altsel_ctrl &= (~mask);
	} else {
		sysctrl->mfa_secsel_ctrl &= (~mask);
		sysctrl->mfa_tersel_ctrl &= (~mask);
		sysctrl->mfa_quatsel_ctrl &= (~mask);
		sysctrl->mfa_debugsel_ctrl &= (~mask);
		sysctrl->mfa_altsel_ctrl &= (~mask);
	}
	wmb();
    
	spin_unlock_irqrestore(&ox820_mf_lock, flags);
}

EXPORT_SYMBOL(ox820_mf_select_gpio);

void ox820_mf_select_static(u32 address_lines, u32 cs_lines)
{
	struct ox820_sysctrl_registers_t* sysctrl = (struct ox820_sysctrl_registers_t*) SYS_CONTROL_BASE;
	struct ox820_secctrl_registers_t* secctrl = (struct ox820_secctrl_registers_t*) SEC_CONTROL_BASE;
	unsigned long flags;
	u32 mfb_lines = address_lines & 0x3FFF;
	u32 mfa_lines = 0x001FF000;

	if(address_lines & (1 << 18)) {
		mfa_lines |= (1 << 23);
	}
	if(address_lines & (1 << 19)) {
		mfa_lines |= (1 << 24);
	}
	if(address_lines & (1 << 20)) {
		mfa_lines |= (1 << 30);
	}
	if(address_lines & (1 << 21)) {
		mfa_lines |= (1 << 31);
	}
    
	if(cs_lines & (1 << 0)) {
		mfa_lines |= (1 << 22);
	}
	if(cs_lines & (1 << 1)) {
		mfa_lines |= (1 << 25);
	}

	spin_lock_irqsave(&ox820_mf_lock, flags);
	secctrl->mfb_secsel_ctrl |= (mfb_lines);
	secctrl->mfb_tersel_ctrl &= (~mfb_lines);
	secctrl->mfb_quatsel_ctrl &= (~mfb_lines);
	secctrl->mfb_debugsel_ctrl &= (~mfb_lines);
	secctrl->mfb_altsel_ctrl &= (~mfb_lines);
    
	sysctrl->mfa_secsel_ctrl |= (mfa_lines);
	sysctrl->mfa_tersel_ctrl &= (~mfa_lines);
	sysctrl->mfa_quatsel_ctrl &= (~mfa_lines);
	sysctrl->mfa_debugsel_ctrl &= (~mfa_lines);
	sysctrl->mfa_altsel_ctrl &= (~mfa_lines);
    
	wmb();
    
	spin_unlock_irqrestore(&ox820_mf_lock, flags);
}

EXPORT_SYMBOL(ox820_mf_select_static);
