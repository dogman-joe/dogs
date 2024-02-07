#ifndef _ARCH_PROTO_H
#define _ARCH_PROTO_H

#include "types.h"

extern void process(u32 num);

extern void enable_interrupt_controller();
extern void dog_spawn();

extern void write_vbar();

extern void plat_init();

#endif   /* _ARCH_PROTO_H */
