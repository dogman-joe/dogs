#ifndef PROTO_H_
#define PROTO_H_

/* Definitions of global variables and functions usedin multiple files in top
 * layer of kernel code */

/* SHOULD onlybe included in notmain */

#include "dogtypes.h"

#include "dogproc.h"

extern void dogproc_init(void);
extern void dogclock_init(void);
extern void start_dogtime(void);

extern void arch_init();

extern void irq_init();

extern int dogprint(char *s);
#endif   /* PROTO_H_ */
