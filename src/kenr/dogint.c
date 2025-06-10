#include "dogint.h"

/* number of lists of IRQ hooks, one list per supported line. */
static irq_hook_t* irq_dogs[NUM_IRQ] = {0};

void put_dogint_handler(u32 irq, irq_hook_t* irq_hook) {
  irq_dogs[irq] = irq_hook;

  return;
}

void irq_handle(u32 irq) {
  irq_hook_t *hook = irq_dogs[irq];
  void (*handle_ptr)(void) = hook->handler;
  (*handle_ptr)();

  return;
}
