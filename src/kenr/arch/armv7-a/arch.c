#include "arch.h"
#include "proto.h"

extern int exc_vector_table;

void arch_init()
{
  write_vbar((u32) &exc_vector_table);

  plat_init();
}
