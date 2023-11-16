#include "dogint.h"

extern void dogtick();

void put_dogint_handler(u32 irq, irq_hook_t* irq_hook)
{
  irq_dogs[irq] = irq_hook;
}

void irq_handle(unsigned int irq)
{
  irq_hook_t *hook = irq_dogs[irq];

  void (*handle_ptr)(void) = hook->handler;
  (*handle_ptr)();

  return;
}
