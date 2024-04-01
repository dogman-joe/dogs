#include "types.h"
#include "plat_proto.h"
#include "am335x_intr_regs.h"

void plat_irq_unmask(u8 irq) {
  int irq_bit = 1 << (irq % 32);

  PUT32(INTC_MIR_CLEAR_BANK(irq), irq_bit);

  return;
}

void irq_init() {
  PUT32(INTC_SYSCONFIG, 0x02);

  while (1) {
    if ((GET32(INTC_SYSSTATUS) & 0x01) == 1)
      break;
  }

  return;
}

void plat_irq_handle() {
  u32 irq_n;

  irq_n = (GET32(INTC_SIR_IRQ) & INTC_IRQ_N_MASK);

  if (irq_n == 68)
    irq_n = 0;

  irq_handle(irq_n);

  PUT32(INTC_CONTROL, 0x01);

  return;
}
