#ifndef DOGCLOCK_H_
#define DOGCLOCK_H_

#include "dogtypes.h"

#define DOG_CLOCK_IRQ_N 0x00

extern void put_dogint_handler(u32 irq, irq_hook_t* irq_hook);

extern void arch_start_dogtime();
extern void arch_clock_irq_handle();

extern void schedog();
extern void enable_irq();
extern void disable_irq();

static struct dogclock_info dogclock;   /* dog clock table */

#endif  /*DOGCLOCK_H_*/
