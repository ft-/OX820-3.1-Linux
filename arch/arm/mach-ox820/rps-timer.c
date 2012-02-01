/*
 * arch/arm/mach-ox820/rps-time.c
 *
 * Copyright (C) 2009 Oxford Semiconductor Ltd
 *
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
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/io.h>
#include <linux/clockchips.h>
#include <linux/clocksource.h>
#include <linux/time.h>
#include <asm/smp_twd.h>
#include <asm/mach/time.h>
#include <mach/hardware.h>
#include <mach/rps-timer.h>
#include <mach/rps-irq.h>
#include <mach/hw/rpsa.h>

static struct clock_event_device ckevt_rps_timer1;

static int oxnas_rps_set_next_event(unsigned long delta, struct clock_event_device* unused)
{
	struct ox820_rpsa_registers_t* const rpsa = (struct ox820_rpsa_registers_t*)RPSA_BASE;

	if (delta == 0) {
		return -ETIME;
	}

	/* Stop timers before programming */
	rpsa->timer1_control = 0;
	wmb();

	/* Setup timer 1 load value */
	rpsa->timer1_load = delta;
	wmb();

	/* Setup timer 1 prescaler, periodic operation and start it */
	rpsa->timer1_control =	(TIMER_1_PRESCALE_ENUM << TIMER_PRESCALE_BIT) |
				(TIMER_1_MODE          << TIMER_MODE_BIT)     |
				(TIMER_ENABLE_ENABLE   << TIMER_ENABLE_BIT);
	wmb();

	return 0;
}

static void oxnas_rps_set_mode(enum clock_event_mode mode, struct clock_event_device *dev)
{
	struct ox820_rpsa_registers_t* const rpsa = (struct ox820_rpsa_registers_t*)RPSA_BASE;
	switch(mode) {
		case CLOCK_EVT_MODE_PERIODIC:
			/* Stop timers before programming */
			rpsa->timer1_control = 0;
			wmb();

			/* Set period to match HZ */
			rpsa->timer1_load = TIMER_1_LOAD_VALUE;
			wmb();

			/* Setup prescaler, periodic operation and start it */
			rpsa->timer1_control =	(TIMER_1_PRESCALE_ENUM << TIMER_PRESCALE_BIT) |
						(TIMER_1_MODE          << TIMER_MODE_BIT)     |
						(TIMER_ENABLE_ENABLE   << TIMER_ENABLE_BIT);
			wmb();
			break;

		case CLOCK_EVT_MODE_ONESHOT:
		case CLOCK_EVT_MODE_UNUSED:
		case CLOCK_EVT_MODE_SHUTDOWN:
		default:
			/* Stop timer */
			rpsa->timer1_control &= ~(TIMER_ENABLE_ENABLE   << TIMER_ENABLE_BIT);
			break;
	}
}

static irqreturn_t OXNAS_RPS_timer_interrupt(int irq, void *dev_id)
{
	struct ox820_rpsa_registers_t* const rpsa = (struct ox820_rpsa_registers_t*)RPSA_BASE;
	/* Clear the timer interrupt - any write will do */
	rpsa->timer1_clear_interrupt = 0;
	wmb();

	/* Quick, to the high level handler... */
	if(ckevt_rps_timer1.event_handler) {
		ckevt_rps_timer1.event_handler(&ckevt_rps_timer1);
	}

	return IRQ_HANDLED;
}

static struct irqaction oxnas_timer_irq = {
 	 .name		= "RPSA timer1",
 	 .flags		= IRQF_DISABLED | IRQF_TIMER | IRQF_IRQPOLL,
 	 .handler	= OXNAS_RPS_timer_interrupt
};

static cycle_t ox820_get_cycles(struct clocksource *cs)
{
	cycle_t time = *((volatile unsigned long*)TIMER2_VALUE);
	return ~time;
}


static struct clocksource clocksource_ox820 = {
	.name	= "rps-timer2",
	.rating	= 200,
	.read	= ox820_get_cycles,
	.mask	= CLOCKSOURCE_MASK(24),
	.shift	= 10,
	.flags	= CLOCK_SOURCE_IS_CONTINUOUS,
};

static void __init ox820_clocksource_init(void)
{
	struct ox820_rpsa_registers_t* const rpsa = (struct ox820_rpsa_registers_t*)RPSA_BASE;

	/* setup timer 2 as free-running clocksource */
	rpsa->timer2_control = 0;
	wmb();
	
	rpsa->timer2_load = 0xffffff;
	wmb();

	rpsa->timer2_control =	(TIMER_PRESCALE_16 << TIMER_PRESCALE_BIT) |
				(TIMER_2_MODE << TIMER_MODE_BIT) |
				(TIMER_ENABLE_ENABLE << TIMER_ENABLE_BIT );
	wmb();

	clocksource_ox820.mult = clocksource_hz2mult((TIMER_INPUT_CLOCK / (1 << (4*TIMER_PRESCALE_16))),
	                                             clocksource_ox820.shift);
/* 	printk("820:start timer 2 clock %dkHz\n", 
		(TIMER_INPUT_CLOCK / (1 << (4*TIMER_PRESCALE_16))));
 */
 	clocksource_register(&clocksource_ox820);
}

void oxnas_init_time(void) {
#ifdef CONFIG_LOCAL_TIMERS
	twd_base = __io_address(OX820_TWD_BASE);
#endif

	ckevt_rps_timer1.name = "RPSA-timer1";
	ckevt_rps_timer1.features = CLOCK_EVT_FEAT_PERIODIC;
	ckevt_rps_timer1.rating = 306;
	ckevt_rps_timer1.shift = 24;
	ckevt_rps_timer1.mult = div_sc(CLOCK_TICK_RATE , NSEC_PER_SEC, ckevt_rps_timer1.shift);
	ckevt_rps_timer1.max_delta_ns = clockevent_delta2ns(0x7fff, &ckevt_rps_timer1);
	ckevt_rps_timer1.min_delta_ns = clockevent_delta2ns(0xf, &ckevt_rps_timer1);
	ckevt_rps_timer1.set_next_event	= oxnas_rps_set_next_event;
	ckevt_rps_timer1.set_mode = oxnas_rps_set_mode;
	ckevt_rps_timer1.cpumask = cpumask_of(0);

	// Connect the timer interrupt handler
	oxnas_timer_irq.handler = OXNAS_RPS_timer_interrupt;
	setup_irq(OX820_RPSA_IRQ_RPSA_TIMER1, &oxnas_timer_irq);

	ox820_clocksource_init();
  	clockevents_register_device(&ckevt_rps_timer1);
}

#ifdef CONFIG_ARCH_USES_GETTIMEOFFSET
/*
 * Returns number of microseconds since last clock tick interrupt.
 * Note that interrupts will be disabled when this is called
 * Should take account of any pending timer tick interrupt
 */
static unsigned long oxnas_gettimeoffset(void)
{
	struct ox820_rpsa_registers_t* const rpsa = (struct ox820_rpsa_registers_t*)RPSA_BASE;
	// How long since last timer interrupt?
	unsigned long ticks_since_last_intr =
					(unsigned long)TIMER_1_LOAD_VALUE - rpsa->timer1_current_count;

	// Is there a timer interrupt pending
	u32 timer_int_pending = rpsa->irq_raw_status & MSK_OX820_RPSA_IRQ_RPSA_TIMER1;

	if (timer_int_pending) {
		// Sample time since last timer interrupt again. Theoretical race between
		// interrupt occuring and ARM reading value before reload has taken
		// effect, but in practice it's not going to happen because it takes
		// multiple clock cycles for the ARM to read the timer value register
		unsigned long ticks2 = (unsigned long)TIMER_1_LOAD_VALUE - rpsa->timer1_current_count;

		// If the timer interrupt which hasn't yet been serviced, and thus has
		// not yet contributed to the tick count, occured before our initial
		// read of the current timer value then we need to account for a whole
		// timer interrupt period
		if (ticks_since_last_intr <= ticks2) {
			// Add on a whole timer interrupt period, as the tick count will have
			// wrapped around since the previously seen timer interrupt (?)
			ticks_since_last_intr += TIMER_1_LOAD_VALUE;
		}
	}

	return TICKS_TO_US(ticks_since_last_intr);
}
#endif // CONFIG_ARCH_USES_GETTIMEOFFSET

struct sys_timer oxnas_timer = {
 	 .init   = oxnas_init_time,
#ifdef CONFIG_ARCH_USES_GETTIMEOFFSET
 	 .offset = oxnas_gettimeoffset,
#endif // CONFIG_ARCH_USES_GETTIMEOFFSET
};
