#include "dogclock.h"
#include "string.h"

extern void  plat_timer_irq_handle();
extern void early_debug_light_led2();

void dogclock_init()
{
  memset(&dogclock, 0, sizeof(struct dogclock_info));

  return;
}

void dogtick()
{
  dogclock.real_time++;
  plat_timer_irq_handle();
  return;
}

void start_dogtime()
{
  irq_hook_t hook;
  hook.handler = &dogtick;

  put_dogint_handler(DOG_CLOCK_IRQ_N, &hook);

  plat_start_dogtime();

  return;
}
