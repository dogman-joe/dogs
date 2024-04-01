#ifndef ARCH_PROTO_H_
#define ARCH_PROTO_H_

#include "types.h"

extern void process(u32 num);

extern void enable_interrupt_controller();
extern void dog_spawn();

extern void write_vbar();

extern void plat_init();

#endif   /* ARCH_PROTO_H_ */
