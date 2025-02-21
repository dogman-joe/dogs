#include "proto.h"
#include "types.h"

extern int dogprint(char *s);

int dogmain(void) {
  struct dogproc kerndog;
  struct dogproc *rootdog = &dogs[0];

  /* architecure specific init */
  arch_init();

  dogprint("\r\n\r\ndogs initializing\r\n");

  /* initialize process table */
  dogproc_init();
  dogprint("dog process table initialized\r\n");

  /* initialize kernel clock data strucutre */
  dogclock_init();
  dogprint("dog global clock initialized\r\n");


  /* initialize interrupts for platform */
  irq_init();
  dogprint("dog arch interrupts initialized\r\n");

  /* start dog tick clock*/
  start_dogtime();
  dogprint("dog global clock has started\r\n");

  dogprint("\r\ndogs setup finished jumping to root task\r\n");

  /* switch to root dog */
  switch_context(&kerndog, rootdog);

  /* never reach!! */
  while (1) {
  }

  return(0);
}
