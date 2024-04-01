#include "stackframe.h"
#include "arch_proto.h"

extern int exc_vector_table;

void arch_dogproc_init(struct stackframe_t *dog, int entry) {
  dog->r0 =(reg_t)entry;
  dog->lr = (reg_t)hello;

  dog->psr = (reg_t)0x13;

  dog->sp = (reg_t)0x402f0400 + ((entry + 1) * 0x1000);

  return;
}

void arch_init() {
  write_vbar((u32) &exc_vector_table);

  plat_init();
}
