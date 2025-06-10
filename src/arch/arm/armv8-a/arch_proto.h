#ifndef ARCH_PROTO_H_
#define ARCH_PROTO_H_

#include "stdint.h"
#include "string.h"
#include "plat_proto.h"
#include "stackframe.h"
#include "drivers.h"

/* hellodog */
#include "libs/hello.h"

/* Arch Proc */

extern reg_t stack_top;

#include "cpu_arch.h"

/* gic_V3 */

#include "drivers/gic_v3.h"

/* Generic Timer */
#include "drivers/generic_timer.h"

/* PL011 */

#include "drivers/PL011.h"

/* Drivers Table */
#define GIC_400_NAME "arm,gic-400"
#define GIC_A15_NAME "arm,cortex-a15-gic"
#define PL011_NAME "arm,pl011"

const driver_table_info gic_400_info = {
  .name = GIC_400_NAME,
  .probe = gic_probe
};

const driver_table_info gic_a15_info = {
  .name = GIC_A15_NAME,
  .probe = gic_probe
};

const driver_table_info intc_driver_table[2] = {
  gic_a15_info,
  gic_400_info
};

const driver_table_info pl011_info = {
  .name = PL011_NAME,
  .probe = pl011_probe
};

const driver_table_info console_driver_table[1] = {
  pl011_info
};

/* dogtb lib */
#include "libs/dogtb.h"

/* dog print */
#include "libs/dogprint.h"

#endif   /* ARCH_PROTO_H_ */
