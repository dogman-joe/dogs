#ifndef _PLAT_PROTO_H
#define _PLAT_PROTO_H

#include "types.h"

//TODO: figure out how to manage CONTROL MODULE data

//Control Module
#define CM_DPLL 0x44E00500
#define CLKSEL_TIMER2_CLK (CM_DPLL+0x08)

#define CM_PER_BASE             0x44E00000
#define CM_PER_L4LS_CLKCTRL       (CM_PER_BASE+0x00)
#define CM_PER_GPIO1_CLKCTRL    (CM_PER_BASE+0xAC)
#define CM_PER_TIMER2_CLKCTRL (CM_PER_BASE+0x80)


// IO
#define GET8(a)     (*(volatile u8 *)(a))
#define PUT8(a,v)   (*(volatile u8 *)(a) = (v))
#define GET16(a)    (*(volatile u16 *)(a))
#define PUT16(a,v)  (*(volatile u16 *)(a) = (v))
#define GET32(a)    (*(volatile u32 *)(a))
#define PUT32(a,v)  (*(volatile u32 *)(a) = (v))

void plat_timer_init();
void plat_timer_start();

#endif   /* _PLAT_PROTO_H */
