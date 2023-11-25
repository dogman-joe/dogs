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

  light_led(0);

  /* initialize interrupts for platform */
  irq_init();

  start_dogtime();

  int ra,rb = 0;

  // cause delay for timer IRQ to be activated before reaching final while loop
  for(rb = 0; rb < 0x20000;rb++)
    ra++;

  light_led(2);

  // swicth to init user proc
  struct dogproc *dog = &dogs[1];

  switch_context((unsigned int) dog);

  // never reach!!
  while(1)
    {
    }

  return(0);
}
