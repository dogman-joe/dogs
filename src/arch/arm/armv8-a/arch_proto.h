#ifndef ARCH_PROTO_H_
#define ARCH_PROTO_H_

#include "stdint.h"
#include "string.h"
#include "plat_proto.h"
#include "types.h"
#include "stackframe.h"
#include "drivers.h"

/* hellodog */

extern void process(u32 num);

/* Arch Proc */

extern reg_t stack_top;

extern void enable_interrupt_controller();
extern void dog_spawn();

extern void write_vbar();

/* gic_V3 */

typedef struct {
  u64 gic_ifregs_base;
  u64 gic_dregs_base;
} gic_plat_config;

extern void gic_eoi(u32 irq);
extern void gic_init(const gic_plat_config *gic_config);
extern u16 gicc_acknowledge_int();

/* Generic Timer */

#define GENERIC_TIMER_INT_NO 27

u32 cntfrq; /* generic timer frequency */

extern void generic_timer_init();
extern void generic_timer_handle();

/* Drivers Table */
#define GIC_400_NAME "arm,gic-400"
#define GIC_A15_NAME "arm,cortex-a15-gic"
#define PL011_NAME "arm,pl011"

extern int gic_probe(dt_node_info *pl011_node_info);

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

extern int pl011_probe(dt_node_info *pl011_node_info);

const driver_table_info pl011_info = {
  .name = PL011_NAME,
  .probe = pl011_probe
};

const driver_table_info console_driver_table[1] = {
  pl011_info
};

/* Device Tree */

typedef struct {
  uint32_t magic; /* 0xD00DFEED */
  uint32_t size; /* includes header and data */
  uint32_t struct_offset; /* offset of struct block */
  uint32_t strings_offset; /* offset of strings block */
  uint32_t memory_offset; /* offset of memory block */
  uint32_t version; /* version of dtb (17) */
  uint32_t min_version; /* minimum version (16) */
  uint32_t cpu_id; /* id of boot cpu */
  uint32_t strings_size; /* size of strings block */
  uint32_t struct_size; /* size of struct block */
} dtb_header;

extern dt_node_info* find_compatible(dtb_header *head, const char *name);

/* Console */
typedef u64 console;

extern void dogprint_init(console *console_base);
extern int dogprint(char *s);
extern int dogprintnum(u32 x);
extern int dogprintnum64(u64 x);

/* IRQ */

extern void enable_irq();
extern void irq_handle(unsigned int irq);


#endif   /* ARCH_PROTO_H_ */
