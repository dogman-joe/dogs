#include "proto.h"

int notmain(void) {
  /* initialize process table */
  dogproc_init();

  /* initialize kernel clock data strucutre */
  dogclock_init();

  /* architecure specific init */
  arch_init();

  /* initialize interrupts for platform */
  irq_init();

  /* start dog tick clock*/
  start_dogtime();

  struct dogproc olddog;
  struct dogproc *dog = &dogs[0];

  /* switch to first dog */
  switch_context(&olddog, dog);

  /* never reach!! */
  while (1) {
  }

  return(0);
}
