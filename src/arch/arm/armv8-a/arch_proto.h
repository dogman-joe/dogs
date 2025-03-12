#ifndef ARCH_PROTO_H_
#define ARCH_PROTO_H_

#include "plat_proto.h"
#include "types.h"
#include "stackframe.h"

extern reg_t stack_top;

/* hellodog */

extern void process(u32 num);

extern void enable_interrupt_controller();
extern void dog_spawn();

extern void write_vbar();

/* gic_V3 */

typedef struct {
  u64 gic_ifregs_base;
  u64 gic_dregs_base;
} gic_plat_config;

static const gic_plat_config plat_gic_config = {
  .gic_ifregs_base = GICC_BASE,
  .gic_dregs_base = GICD_BASE
};

extern void gic_eoi(u32 irq);
extern void gic_init(const gic_plat_config *gic_config);
extern u16 gicc_acknowledge_int();

/* Generic Timer */

#define GENERIC_TIMER_INT_NO 27

u32 cntfrq; /* generic timer frequency */

extern void generic_timer_init();
extern void generic_timer_handle();

/* PL011 */

typedef volatile struct __attribute__((packed)) {
        u32 DR;                 /* 0x0 Data Register */
        u32 RSRECR;             /* 0x4 Receive status / error clear register */
        u32 _reserved0[4];      /* 0x8 - 0x14 reserved */
        const u32 FR;           /* 0x18 Flag register */
        u32 _reserved1;         /* 0x1C reserved */
        u32 ILPR;               /* 0x20 Low-power counter register */
        u32 IBRD;               /* 0x24 Integer baudrate register */
        u32 FBRD;               /* 0x28 Fractional baudrate register */
        u32 LCRH;               /* 0x2C Line control register */
        u32 CR;                 /* 0x30 Control register */
        u32 IFLS;               /* 0x34 Interrupt FIFO level select register */
        u32 IMSC;               /* 0x38 Interrupt Mask set/clear register */
        u32 RIS;                /* 0x3c Raw Interrupt Status register */
        u32 MIS;                /* 0x40 Masked Interrupt Status register */
        u32 ICR;                /* 0x44 Interrupt Clear register */
        u32 DMACR;              /* 0x48 DMA control register */
} pl011_registers;

pl011_registers *console;

extern int pl011_init(pl011_registers *base);

/* Console */

extern void dogprint_init();
extern int dogprint(char *s);
extern int dogprintnum(u64 x);

extern void enable_irq();
extern void irq_handle(unsigned int irq);

#endif   /* ARCH_PROTO_H_ */
