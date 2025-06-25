#ifndef DOGPROC_H_
#define DOGPROC_H_

#include "types.h"
#include "arch/arch.h"

/* Dog proc Structure */
struct dogproc {
  struct stackframe_t p_reg;   /* process' registers saved in stack frame */
  u32 did;                     /* dog process id */
  u32 p_magic;
};


void dogproc_init(void);

void jump_to_rootdog();

void switch_context(struct dogproc *, struct dogproc *);

#define DOG_PROC_MAGIC 0xBADB

#endif /* DOGPROC_H_ */
