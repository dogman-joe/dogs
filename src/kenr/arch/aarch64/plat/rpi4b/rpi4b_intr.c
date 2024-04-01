#include "plat_proto.h"

void plat_irq_unmask(u32 irq) {
  PUT32(ENABLE_IRQS(irq), irq);
  return;
}

void plat_handle_irq(void) {
  unsigned int irq_n = GET32(IRQ_PENDING_0);

  if (irq_n == SYSTEM_TIMER_IRQ_1)
    irq_n = 0;

  irq_handle(irq_n);

  return;
}

void irq_init() {
  enable_irq();

  return;
}
