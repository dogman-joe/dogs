#ifndef DOGINT_H_
#define DOGINT_H_

#include "dogtypes.h"

#define NUM_IRQ 80

extern void dogtick();

/* number of lists of IRQ hooks, one list per supported line. */
static irq_hook_t* irq_dogs[NUM_IRQ] = {0};

#endif   /* DOGINT_H_ */
