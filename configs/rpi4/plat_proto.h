#ifndef PLAT_PROTO_H_
#define PLAT_PROTO_H_

#include "types.h"
#include "arch/armv7-a/io.h"

#define UART0_BASE        ((unsigned int *)(0xFE201000))

#define GICD_BASE (0xFF841000)
#define GICC_BASE (0xFF842000)

#endif   /* PLAT_PROTO_H_ */
