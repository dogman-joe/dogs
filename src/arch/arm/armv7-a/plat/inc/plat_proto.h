#ifndef PLAT_PROTO_H_
#define PLAT_PROTO_H_

#include "types.h"
#include "arch/armv7-a/io.h"

#define CM_DPLL 0x44E00500
#define CLKSEL_TIMER2_CLK (CM_DPLL+0x08)

#define CM_PER_BASE             (0x44E00000)
#define CM_PER_L4LS_CLKCTRL     (CM_PER_BASE+0x00)
#define CM_PER_GPIO1_CLKCTRL    (CM_PER_BASE+0xAC)
#define CM_PER_TIMER2_CLKCTRL   (CM_PER_BASE+0x80)

extern void plat_irq_unmask(u8 irq);

extern void irq_handle(u32);

void plat_timer_init();
void plat_timer_start();

#endif /* PLAT_PROTO_H_ */
