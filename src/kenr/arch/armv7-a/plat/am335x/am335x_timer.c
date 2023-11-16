#include "plat_proto.h"
#include "am335x_timer_regs.h"

struct am335x_timer *dtimer;

//TODO: replace PUT statements with structrue or vice versa decied reasoning for this?
void plat_timer_init()
{

  PUT32(CM_PER_TIMER2_CLKCTRL,2);

  while(1)
    {
      if((GET32(CM_PER_TIMER2_CLKCTRL)&0x00030000)==0) break;
    }

  PUT32(CM_PER_L4LS_CLKCTRL,2);

  PUT32(CLKSEL_TIMER2_CLK,1);

  dtimer = (struct am335x_timer *)DMTIMER2_BASE;
  dtimer->IRQEN_SET = (u32)0x02;
  dtimer->TIOCP_CFG[0] = (u32)0x0;
  dtimer->TLDR = (u32)0xfffff000;
  dtimer->TCRR = (u32)0xfffff000;

}

void plat_timer_start()
{
  dtimer->TCLR=  (u32)0x01;
}

void plat_timer_irq_handle()
{

  dtimer->IRQ_EOI =  (u32)0x00;
  dtimer->IRQ_STAT = (u32)0x07;
}
