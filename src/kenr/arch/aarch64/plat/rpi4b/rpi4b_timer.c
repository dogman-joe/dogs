#include "plat_proto.h"
#include "rpi4b_timer_regs.h"

struct rpi4b_timer *pi_timer;

void plat_timer_init()
{
  pi_timer = (struct rpi4b_timer *)TIMER_BASE;

  plat_irq_unmask(SYSTEM_TIMER_IRQ_1);

  pi_timer->TIMER_C1 = pi_timer->TIMER_CL0 + 0x200;

  return;
}

void plat_timer_irq_handle()
{
  pi_timer->TIMER_C1 = pi_timer->TIMER_CL0 + 0x200;

  pi_timer->TIMER_CS = TIMER_CS_M1;

  return;
}

void plat_start_dogtime()
{
  plat_timer_init();

  return;
}
