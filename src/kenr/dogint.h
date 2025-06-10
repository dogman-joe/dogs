#ifndef DOGINT_H_
#define DOGINT_H_

#include "dogclock.h"
#include "types.h"

#define NUM_IRQ 80

/* IRQ Hook Structure */
typedef struct irq_hook {
  void (*handler)(void);
  u32 irq_num;
} irq_hook_t;

void put_dogint_handler(u32 irq, irq_hook_t* irq_hook);
void irq_handle(u32 irq);


#endif   /* DOGINT_H_ */
