/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _ox820_mach_leon_h
#define _ox820_mach_leon_h

#include <linux/types.h>
#include <linux/dma-mapping.h>
#include <linux/platform_device.h>

int ox820_request_leon(struct platform_device* dev);

int ox820_release_leon(struct platform_device* dev);

int ox820_start_leon(dma_addr_t startaddr);
int ox820_stop_leon(void);

enum ox820_leon_clockmode_t
{
	OX820_LEON_CLOCKMODE_DIV_4,
	OX820_LEON_CLOCKMODE_DIV_2
};
int ox820_set_clock(enum ox820_leon_clockmode_t);

int ox820_is_leon_running(void);

int ox820_leon_trigger_irq2(void);

/* only one of the two can be used */
int ox820_leon_trigger_rps_softirq(void);

#endif
