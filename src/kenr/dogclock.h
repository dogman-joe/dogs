#ifndef DOGCLOCK_H_
#define DOGCLOCK_H_

#include "dogint.h"
#include "arch/arch.h"

#define DOG_CLOCK_IRQ_N 0x00

void dogclock_init(void);
void start_dogtime(void);
void schedog();

#endif  /*DOGCLOCK_H_*/
