#include "dogproc.h"

void dogproc_init(void)
{
  struct dogproc * dog;
  u32 i = 0;

  for (dog = BEG_PROC_ADDR, i = 0; i < NUM_DOGS; dog++, i++)
    {
      dog->p_reg.r0 = 1 << (i + 1);

      dog->did = i;
    }

  return;
}
