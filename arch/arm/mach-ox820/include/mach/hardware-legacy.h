/* RPS timer setup */
#define TIMER_1_MODE           TIMER_MODE_PERIODIC
#define TIMER_2_PRESCALE_ENUM  TIMER_PRESCALE_256
#define TIMER_2_MODE           TIMER_MODE_FREE_RUNNING

/* Useful macros for dealing with sub timer-interrupt intervals - preserve
 * as much precision as possible without using floating point and minimising
 * runtime CPU requirement */
#define TIMER_1_LOAD_VALUE     ((CLOCK_TICK_RATE) / HZ)
#define TICKS_TO_US_SCALING    1024
#define TICKS_TO_US_FACTOR     (((2 * TICKS_TO_US_SCALING * 1000000) + CLOCK_TICK_RATE) / (2 * CLOCK_TICK_RATE))
#define TICKS_TO_US(ticks)     ((((ticks) * TICKS_TO_US_FACTOR * 2) + TICKS_TO_US_SCALING) / (2 * TICKS_TO_US_SCALING))

/* Remap and pause */
#define RPS_REMAP_AND_PAUSE    (RPS_BASE + 0x300)

#define USBA_POWO_SEC_MFP  10
#define USBA_OVERI_SEC_MFP 11
#define USBA_POWO_TER_MFP  48
#define USBA_OVERI_TER_MFP 49

#define USBB_POWO_SEC_MFP  28
#define USBB_OVERI_SEC_MFP 29
#define USBB_POWO_TER_MFP  5
#define USBB_OVERI_TER_MFP 0

/* RPS GPIO registers */
#define RPS_GPIO_BASE                         (RPS_BASE + 0x3C0)
#define RPS_GPIO_OUTPUT                       (RPS_BASE + 0x3C0)
#define RPS_GPIO_OUTPUT_ENABLE                (RPS_BASE + 0x3C4)
#define RPS_GPIO_INTERRUPT_ENABLE             (RPS_BASE + 0x3C8)
#define RPS_GPIO_INTERRUPT_EVENT              (RPS_BASE + 0x3CC)
#define RPS_GPIO_CHIPID                       (RPS_BASE + 0x3FC)

/* Timer registers */
#define RPS_TIMER_BASE  (RPSA_BASE + 0x200)
#define RPS_TIMER1_BASE (RPS_TIMER_BASE)
#define RPS_TIMER2_BASE (RPS_TIMER_BASE + 0x20)

#define RPS_TIMER1_LOAD    (RPS_TIMER1_BASE + 0x0)
#define RPS_TIMER1_VALUE   (RPS_TIMER1_BASE + 0x4)
#define RPS_TIMER1_CONTROL (RPS_TIMER1_BASE + 0x8)
#define RPS_TIMER1_CLEAR   (RPS_TIMER1_BASE + 0xc)

#define RPS_TIMER2_LOAD    (RPS_TIMER2_BASE + 0x0)
#define RPS_TIMER2_VALUE   (RPS_TIMER2_BASE + 0x4)
#define RPS_TIMER2_CONTROL (RPS_TIMER2_BASE + 0x8)
#define RPS_TIMER2_CLEAR   (RPS_TIMER2_BASE + 0xc)

#define RPS_TIMER_MODE_BIT          6
#define RPS_TIMER_MODE_FREE_RUNNING 0
#define RPS_TIMER_MODE_PERIODIC     1
#define RPS_TIMER_ENABLE_BIT        7
#define RPS_TIMER_ENABLE_DISABLE    0
#define RPS_TIMER_ENABLE_ENABLE     1

/* Remap and pause */
#define RPS_REMAP_AND_PAUSE    (RPS_BASE + 0x300)


/* Std PCI configuration registers */
#define PCI_CONFIG_VERSION_DEVICEID_REG_OFFSET	0x00
#define PCI_CONFIG_COMMAND_STATUS_REG_OFFSET	0x04
