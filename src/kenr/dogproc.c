#include "dogproc.h"
#include "string.h"

int cur, next;

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
