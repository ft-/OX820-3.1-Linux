/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _ox820_gmac_pd_h
#define _ox820_gmac_pd_h

#include <linux/types.h>

struct ox820_gmac_platform_data_t {
	unsigned int enable_leon;
	unsigned int enable_netoe;
	int phy_adr;
};

#endif
