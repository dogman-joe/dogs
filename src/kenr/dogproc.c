#include "arch/arch.h"
#include "dogproc.h"
#include "string.h"

int cur, next;

#define NUM_DOGS       0x03

struct dogproc dogs[NUM_DOGS];   /* process table */

/* Proc Table */
#define BEG_PROC_ADDR (&dogs[0])



struct dogproc dogs[NUM_DOGS];  /* process table */

void schedog() {
  next = (cur + 1) % 3;

  struct dogproc *olddog = &dogs[cur];
  struct dogproc *dog = &dogs[next];

  cur = next;
  switch_context(olddog, dog);

  return;
}

void jump_to_rootdog() {
  /* root dog proc */
  struct dogproc *rootdog = &dogs[0];
  /* kernel dog proc */
  struct dogproc kerndog;
  switch_context(&kerndog, rootdog);

  return;
}

void dogproc_init(void) {
  struct dogproc * dog;
  cur = 0;
  next = 0;
  u32 i = 0;

  for (dog = BEG_PROC_ADDR, i = 0; i < NUM_DOGS; dog++, i++) {
    memset(dog, 0, sizeof(struct dogproc));
    dog->did = i;

    arch_dogproc_init(&dog->p_reg, i);
  }

  return;
}
