/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _ox820_hw_cipher_h
#define _ox820_hw_cipher_h

#include <linux/types.h>

struct ox820_netoe_registers_t
{
	u32 job_queue_base_address;
	u32 job_queue_fill_level;
	u32 job_queue_read_pointer;
	u32 job_queue_write_pointer;
	u32 status;
	u32 jobs_completed;
	u32 bytes_transmitted;
	u32 packets_transmitted;
};

#endif
