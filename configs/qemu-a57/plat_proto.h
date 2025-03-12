#ifndef PLAT_PROTO_H_
#define PLAT_PROTO_H_

#include "types.h"
#include "arch/armv7-a/io.h"

#define UART0_BASE        ((unsigned int *)(0x09000000))

#define GIC_BASE 0x08000000

#define GICD_BASE (GIC_BASE)
#define GICC_BASE (GIC_BASE + 0x10000)

#endif   /* PLAT_PROTO_H_ */
