#include "types.h"
#include "arch/armv8-a/io.h"
#include "drivers.h"

/* TODO: Flesh out driver more */

/* 8.13.7 GICC_CTLR, CPU Interface Control Register */
#define GICC_CTLR_ENABLE        (0x1)   /* Enable GICC */
#define GICC_CTLR_DISABLE       (0x0)   /* Disable GICC */

/* 8.9.4 GICD_CTLR, Distributor Control Register */
#define GIC_GICD_CTLR_ENABLE    (0x1)   /* Enable GICD */
#define GIC_GICD_CTLR_DISABLE   (0x0)   /* Disable GICD */

#define GIC_INT_MAX             (0x40)

/* 8.9.7 GICD_ICFGR<n>, Interrupt Configuration Registers */
#define GIC_GICD_ICFGR_LEVEL    (0x0)   /* level-sensitive */
#define GIC_GICD_ICFGR_EDGE     (0x2)   /* edge-triggered */

#define GIC_PRI_MASK            (0x0f)

#define GIC_GICD_ITARGETSR_CORE0_TARGET_BMAP (0x01010101) /* CPU interface 0 */
#define CIAR_ID_MASK            (0x3FFu)

#define GIC_GICD_ICENABLER_PER_REG (32)
#define GIC_GICD_ISENABLER_PER_REG (32)
#define GIC_GICD_ICPENDR_PER_REG (32)

#define GIC_GICD_ITARGETSR_PER_REG      (4)
#define GIC_GICD_ITARGETSR_SIZE_PER_REG (8)

#define GIC_GICD_IPRIORITY_PER_REG      (4)
#define GIC_GICD_IPRIORITY_SIZE_PER_REG (8)

#define GIC_GICD_ICFGR_PER_REG         (16)
#define GIC_GICD_ICFGR_SIZE_PER_REG    (2)

typedef volatile struct __attribute__((packed)) {
  u32 DCTLR;              /* Distributor Control Reg*/
  const u32 DTYPER;       /* Distributor Type Reg*/
  const u32 DIIDR;        /* Distributor Implementation ID Reg*/
  u32 reserved0[29];
  u32 DIGROUPR[32];
  u32 DISENABLER[32];     /* Distributor set enable */
  u32 DICENABLER[32];     /* Distributor clear enable */
  u32 DISPENDR[32];       /* Distributor set pending */
  u32 DICPENDR[32];       /* Distributor clear pending */
  u32 DICDABR[32];        /* Distributor Active Bit */
  u32 reserved1[32];
  u32 DIPRIORITY[255];    /* Distributor Priority */
  u32 reserved2;
  u32 DITARGETSR[246];    /* Distributor CPU target */
  u32 reserved3;
  u32 DICFGR[64];         /* Distributor config reg */
} gic_distributor_regs;

typedef volatile struct __attribute__((packed)) {
  u32 CCLTR;              /* CPU Interface Control */
  u32 CCPMR;              /* Interrupt priority mask */
  u32 CBPR;               /* Binary Point reg */
  const u32 CIAR;         /* Interrupt acknowledge */
  u32 CEOIR;              /* End of interrupt */
  u32 CRPR;               /* Running priority  */
  u32 CHPPIR;             /* Higher priority INT pending */
  u32 CABPR;              /* Aliased binary point */
  u32 CAIAR;              /* Aliased binary point */
  u32 CAEOIR;             /* Aliased end of INT */
  u32 CAHPPIR;            /* Aliased higher priority INT*/
} gic_cpu_interface_regs;

typedef u32 irq_no;       /* IRQ no */

static gic_distributor_regs *gic_dregs;
static gic_cpu_interface_regs *gic_ifregs;

typedef struct {
  gic_cpu_interface_regs *gic_ifregs_base;
  gic_distributor_regs   *gic_dregs_base;
} gic_plat_config;


static gic_plat_config plat_gic_config = {
  .gic_ifregs_base = 0,
  .gic_dregs_base = 0
};

static void gicd_disable_int(irq_no irq) {
  u8 reg, bit;
  u32 reg_val;

  reg = irq / GIC_GICD_ICENABLER_PER_REG;
  bit = irq % GIC_GICD_ICENABLER_PER_REG;

  reg_val = GET32(&gic_dregs->DICENABLER[reg]);
  reg_val |= (1u << bit);

  PUT32(&gic_dregs->DICENABLER[reg], reg_val);

  return;
}

static void gicd_enable_int(irq_no irq) {
  u8 reg, bit;
  u32 reg_val;

  reg = irq / GIC_GICD_ISENABLER_PER_REG;
  bit = irq % GIC_GICD_ISENABLER_PER_REG;

  reg_val = GET32(&gic_dregs->DISENABLER[reg]);
  reg_val |= (1u << bit);

  PUT32(&gic_dregs->DISENABLER[reg], reg_val);

  return;
}

void gicd_clear_pending(irq_no irq) {
  u8 reg, bit;
  u32 reg_val;

  reg = irq / GIC_GICD_ICPENDR_PER_REG;
  bit = irq % GIC_GICD_ICPENDR_PER_REG;

  reg_val = GET32(&gic_dregs->DICPENDR[reg]);
  reg_val |= (1u << bit);

  PUT32(&gic_dregs->DICPENDR[reg], reg_val);

  return;
}
static void gicd_set_target(irq_no irq, u32 cpu_id) {
  u8 reg, bit;
  u32 reg_val;

  reg = irq / GIC_GICD_ITARGETSR_PER_REG;
  bit = (irq % GIC_GICD_ITARGETSR_PER_REG) * GIC_GICD_ITARGETSR_SIZE_PER_REG;

  reg_val = GET32(&gic_dregs->DITARGETSR[reg]);
  reg_val &= ~(((u32)(0xff)) << bit);
  reg_val |= (cpu_id << bit);

  PUT32(&gic_dregs->DITARGETSR[reg], reg_val);

  return;
}

static void gicd_set_priority(irq_no irq, u32 prio) {
  u8 reg, bit;
  u32 reg_val;

  reg = irq / GIC_GICD_IPRIORITY_PER_REG;
  bit = (irq % GIC_GICD_IPRIORITY_PER_REG) * GIC_GICD_IPRIORITY_SIZE_PER_REG;

  reg_val = GET32(&gic_dregs->DIPRIORITY[reg]);

  reg_val &= ~(((u32)(0xff)) << bit);
  reg_val |= (prio << bit);

  PUT32(&gic_dregs->DIPRIORITY[reg], reg_val);

  return;
}

static void gicd_config(irq_no irq, unsigned int config) {
  u8 reg, bit;
  u32 reg_val;

  reg = irq / GIC_GICD_ICFGR_PER_REG;
  bit = (irq % GIC_GICD_ICFGR_PER_REG) * GIC_GICD_ICFGR_SIZE_PER_REG;

  reg_val = GET32(&gic_dregs->DICFGR[reg]);

  reg_val &= ~(((u32)(0x03)) << bit);
  reg_val |= (((u32)config) << bit);
  PUT32(&gic_dregs->DICFGR[reg], reg_val);

  return;
}

u16 gicc_acknowledge_int(void) {
  return GET32(&gic_ifregs->CIAR) & 0xfff;
}

void gic_eoi(irq_no irq) {
  PUT32(&gic_ifregs->CEOIR, irq);

  return;
}

void gic_unregister_int(irq_no irq) {
  gicd_disable_int(irq);
}

void gic_register_int(irq_no irq) {
  gicd_config(irq, GIC_GICD_ICFGR_EDGE);
  gicd_set_priority(irq, 0x00);
  gicd_set_target(irq, 0x1);
  gicd_clear_pending(irq);
  gicd_enable_int(irq);

  return;
}

#define GICC_PMR_PRI_MIN       (0xff)       /* The lowest level mask */

void init_gicc() {
  PUT32(&gic_ifregs->CCPMR, GICC_PMR_PRI_MIN);
  PUT32(&gic_ifregs->CCLTR, GICC_CTLR_ENABLE);

  return;
}

#define GIC_GICD_CTLR_ENABLE  (0x1)
#define GIC_GICD_CTLR_DISABLE (0x0)

void init_gicd() {
  PUT32(&gic_dregs->DCTLR, GIC_GICD_CTLR_DISABLE);
  PUT32(&gic_dregs->DCTLR, GIC_GICD_CTLR_ENABLE);

  return;
}

void gic_init(gic_plat_config *gic_config) {
  gic_dregs = gic_config->gic_dregs_base;
  gic_ifregs = gic_config->gic_ifregs_base;

  init_gicd();
  init_gicc();

  return;
}

void gic_probe(dt_node_info *gic_node_info) {
  plat_gic_config.gic_dregs_base =
        (gic_distributor_regs *)gic_node_info->reg_vals[0];
  plat_gic_config.gic_ifregs_base =
        (gic_cpu_interface_regs *)gic_node_info->reg_vals[2];

  gic_init(&plat_gic_config);

  return;
}
