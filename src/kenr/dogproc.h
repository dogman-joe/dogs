#ifndef	_DOG_PROC_H
#define	_DOG_PROC_H

#include "dogtypes.h"

extern void switch_context (struct dogproc *, struct dogproc *);

extern void arch_dogproc_init(struct stackframe_t *dog, int entry);

#define DOG_PROC_MAGIC 0xBADB
#define NUM_DOGS       0x03

extern struct dogproc dogs[NUM_DOGS];	/* process table */

#endif  /*_DOG_PROC_H */
