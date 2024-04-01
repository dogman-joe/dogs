#ifndef DOGPROC_H_
#define DOGPROC_H_

#include "dogtypes.h"

extern void switch_context(struct dogproc *, struct dogproc *);

extern void arch_dogproc_init(struct stackframe_t *dog, int entry);

#define DOG_PROC_MAGIC 0xBADB
#define NUM_DOGS       0x03

extern struct dogproc dogs[NUM_DOGS];   /* process table */

#endif /* DOGPROC_H_ */
