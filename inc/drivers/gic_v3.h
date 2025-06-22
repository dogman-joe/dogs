#ifndef GIC_V3_H_
#define GIC_V3_H_

#include "drivers.h"

typedef u32 irq_no;       /* IRQ no */

void gic_eoi(u32 irq);
void gic_register_int(u32 irq_no);
u16 gicc_acknowledge_int(void);

int gic_probe(dt_node_info *gic_node_info);

#endif   /* GIC_V3_H_ */
