#include "proto.h"

extern void dummy();
extern void PUT32 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );

//TODO: add debug define macro
extern void dogpio_init ( );
extern void early_debug_light_led();
extern void early_debug_light_led2();
extern void early_debug_light_led3();

int notmain ( void )
{
  /* initialize process table */
  dogproc_init();

  /* initialize kernel clock data strucutre */
  dogclock_init();

  dogpio_init();

  /* architecure specific init */
  arch_init();

  early_debug_light_led();

  /* initialize interrupts for platform */
  irq_init();

  start_dogtime();

  int ra,rb = 0;

  // cause delay for timer IRQ to be activated before reaching final while loop
  for(rb = 0; rb < 0x20000;rb++)
    ra++;

  early_debug_light_led2();

  while(1)
    {
    }

  return(0);
}
