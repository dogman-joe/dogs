#ifndef ARCH_H_
#define ARCH_H_

#include "stackframe.h"

void arch_init();

/* CLOCK */
void arch_clock_irq_handle();
void arch_start_dogtime();

/* PROCESS */
void arch_dogproc_init(struct stackframe_t *dog, int entry);

void enable_irq();
void disable_irq();
void irq_init();

#endif  /* ARCH_H_ */
