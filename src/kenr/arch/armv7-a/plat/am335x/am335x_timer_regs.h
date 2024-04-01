#ifndef AM335X_TIMER_REGS_H_
#define AM335X_TIMER_REGS_H_

#include"types.h"

#define DMTIMER2_BASE 0x48040000

struct am335x_timer {
  u32 TIDR[4];
  u32 TIOCP_CFG[4];
  u32 IRQ_EOI;
  u32 IRQ_STAT_RAW;
  u32 IRQ_STAT;
  u32 IRQEN_SET;
  u32 IRQEN_CLR;
  u32 IRQWAKEEN;
  u32 TCLR;
  u32 TCRR;
  u32 TLDR;
  u32 TTGR;
  u32 TWPS;
  u32 TMAR;
  u32 TCAR1;
  u32 TSICR;
  u32 TCAR2;
}__attribute__((packed, aligned(4)));

#endif   /* AM335X_TIMER_REGS_H_*/
