#include "proto.h"
#include "stackframe.h"

void arch_dogproc_init(struct stackframe_t *dog, int entry)
{
  dog->lr = (reg_t)dog_spawn;
  dog->x19 = (reg_t)process;
  dog->x20 = (reg_t)entry;

  dog->sp = (reg_t)0x400000 + ((entry + 1) * 0x1000);

  return;
}
void arch_init()
{
  write_vbar();
  plat_init();

  return;
}
