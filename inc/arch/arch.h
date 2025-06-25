#ifndef ARCH_H_
#define ARCH_H_

#include "types.h"
#include "stackframe.h"

void arch_init(void);

/* CLOCK */
void arch_clock_irq_handle(void);
dog_status_t arch_start_dogtime(void);

/* PROCESS */
void arch_dogproc_init(struct stackframe_t *dog, int entry);

void enable_irq(void);
void disable_irq(void);
void arch_irq_init(void);

#endif  /* ARCH_H_ */
