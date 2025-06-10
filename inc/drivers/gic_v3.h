#ifndef GIC_V3_H_
#define GIC_V3_H_

typedef struct {
  u64 gic_ifregs_base;
  u64 gic_dregs_base;
} gic_plat_config;

void gic_eoi(u32 irq);
void gic_init(const gic_plat_config *gic_config);
u16 gicc_acknowledge_int();

int gic_probe(dt_node_info *pl011_node_info);

#endif   /* GIC_V3_H_ */
