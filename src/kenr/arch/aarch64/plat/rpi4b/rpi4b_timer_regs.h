#ifndef _RPI4B_TIMER_H
#define _RPI4B_TIMER_H

#include"types.h"

#define TIMER_BASE 0xFE003000

#define TIMER_CS_M0	(1 << 0)
#define TIMER_CS_M1	(1 << 1)
#define TIMER_CS_M2	(1 << 2)
#define TIMER_CS_M3	(1 << 3)

struct rpi4b_timer
{
	u32 TIMER_CS;
	u32 TIMER_CL0;
	u32 TIMER_CHI;
	u32 TIMER_C0;
	u32 TIMER_C1;
	u32 TIMER_C2;
	u32 TIMER_C3;
}__attribute__((packed, aligned(4)));

#endif   /* _RPI4B_TIMER_H */
