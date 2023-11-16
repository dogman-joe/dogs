#ifndef _ARCH_H
#define _ARCH_H
#include "types.h"

// exported arch specific functions
extern void irq_init ( );
extern void write_vbar ( );

#endif   /* _ARCH_H */
