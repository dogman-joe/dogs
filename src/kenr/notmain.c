#include "proto.h"
#include "dogproc.h"

extern void dummy();
extern void switch_context (unsigned int );

//TODO: add debug define macro
extern void dogpio_init ( );
extern void light_led(unsigned int led);

int notmain ( void )
{

  /* initialize process table */
  dogproc_init();

  /* initialize kernel clock data strucutre */
  dogclock_init();

  dogpio_init();

  /* architecure specific init */
  arch_init();


  /* initialize interrupts for platform */
  irq_init();

  /*start_dogtime(); */

  /* swicth to init user proc*/
  struct dogproc *dog = &dogs[0];

  switch_context((unsigned int) dog);

  /* never reach!! */
  while(1)
    {
    }

  return(0);
}
