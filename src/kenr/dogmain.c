#include "dogproc.h"
#include "dogclock.h"
#include "arch/arch.h"
#include "libs/dogprint.h"

int dogmain(void) {
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
  arch_irq_init();
  dogprint("dog arch interrupts initialized\r\n");

  /* start dog tick clock*/
  start_dogtime();
  dogprint("dog global clock has started\r\n");

  dogprint("\r\ndogs setup finished jumping to root task\r\n");

  /* switch to root dog */
  jump_to_rootdog();

  /* never reach!! */
  while (1) {
  }

  return(0);
}
