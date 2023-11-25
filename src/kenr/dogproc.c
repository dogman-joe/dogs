#include "dogproc.h"

#define USR_MODE        0x10

extern void light_led();

void dogproc_init(void)
{
  struct dogproc * dog;
  u32 i = 0;

  for (dog = BEG_PROC_ADDR, i = 0; i < NUM_DOGS; dog++, i++)
    {
      dog->p_reg.r0 = i;
      dog->p_reg.lr = (unsigned int) &light_led;
      dog->p_reg.psr = (unsigned int) USR_MODE;
      dog->p_reg.sp = (unsigned int) 0x402F4000;

      dog->did = i;
    }

  return;
}
