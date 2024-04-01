#include "dogint.h"

void put_dogint_handler(u32 irq, irq_hook_t* irq_hook) {
  irq_dogs[irq] = irq_hook;
  irq_hook = irq_dogs[irq];

  return;
}

void irq_handle(u32 irq) {
  irq_hook_t *hook = irq_dogs[irq];
  void (*handle_ptr)(void) = hook->handler;
  (*handle_ptr)();

  return;
}
