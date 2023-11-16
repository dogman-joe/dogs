#ifndef _DOG_INT_H
#define _DOG_INT_H

#include "dogtypes.h"

#define NUM_IRQ 80

/* number of lists of IRQ hooks, one list per supported line. */
static irq_hook_t* irq_dogs[NUM_IRQ] = {0};

#endif   /* _DOG_INT_H */
