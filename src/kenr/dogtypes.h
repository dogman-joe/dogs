#ifndef DOGTYPES_H_
#define DOGTYPES_H_

#include "types.h"
#include "stackframe.h"
/* Definitions of data structure types used in kernel*/

/* Dog proc Structure */
struct dogproc {
  struct stackframe_t p_reg;   /* process' registers saved in stack frame */
  u32 did;                     /* dog process id */
  u32 p_magic;
};

/* Clock Info Structure */
struct dogclock_info {
  time_t real_time;
};

/* IRQ Hook Structure */
typedef struct irq_hook {
  void (*handler)(void);
  u32 irq_num;
} irq_hook_t;

#endif   /* DOGTYPES_H_ */
