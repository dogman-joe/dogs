#include "arch_proto.h"

void arch_dogproc_init(struct stackframe_t *dog, int entry) {
  dog->lr = (reg_t)dog_spawn;
  dog->x19 = (reg_t)process;
  dog->x20 = (reg_t)entry;

  /* for now we use root tasks sp at static location
   *  TODO: change this to be dynamic */
  dog->sp = (reg_t)&stack_top + ((entry + 1) * 0x4000);

  return;
}

void arch_console_init() {
  /* Enable output to console */
  pl011_init((pl011_registers *)UART0_BASE);
  dogprint_init((pl011_registers *)UART0_BASE);

  return;
}

void arch_start_dogtime() {
  /* aarch64 arch uses generic timer for global clock */
  generic_timer_init();

  return;
}

void arch_handle_irq(void) {
  u16 irq_no = gicc_acknowledge_int();

  /* handle pending irq if generic timer use our dogtick function */
  if (irq_no == GENERIC_TIMER_INT_NO) {
    irq_handle(0);
  } else {
    irq_handle(irq_no);
  }

  return;
}

void arch_clock_irq_handle() {
  /* handle generic timer interrupt after firing */
  generic_timer_handle();
  gic_eoi(27);

  return;
}

void irq_init() {
  /* init gic_v3 */
  gic_init(&plat_gic_config);
  dogprint("initialized GIC\r\n");

  /* unmask IRQ bit in DAIF */
  enable_irq();
  dogprint("unmasked I in DAIF\r\n");

  return;
}

void arch_init() {
  /* set up exeception vector table */
  write_vbar();

  /* init OS console output */
  arch_console_init();

  return;
}
