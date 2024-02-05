#include "dogclock.h"
#include "string.h"

void dogclock_init()
{
  memset(&dogclock, 0, sizeof(struct dogclock_info));

  dogclock.real_time = 1;

  return;
}

void dogtick()
{
  dogclock.real_time++;
  plat_timer_irq_handle();

  if (dogclock.real_time % 0x5000 != 0)
  {
    return;
  }

  enable_irq();
  schedog();
  disable_irq();

  return;
}

void start_dogtime()
{
  irq_hook_t hook;
  hook.handler = dogtick;

  put_dogint_handler(DOG_CLOCK_IRQ_N, &hook);

  plat_start_dogtime();

  return;
}
