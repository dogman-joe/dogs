#ifndef _KENR_PROTO_H
#define _KENR_PROTO_H

/* Definitions of global variables and functions usedin multiple files in top
 * layer of kernel code */

// SHOULD onlybe included in notmain

#include "dogtypes.h"



extern void dogproc_init(void);
extern void dogclock_init(void);
extern void start_dogtime(void);

extern void arch_init();

extern void irq_init();

#endif   /* _KENR_PROTO_H */
