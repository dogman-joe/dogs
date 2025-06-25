#include "types.h"
#include "stddef.h"
#include "arch/armv8-a/io.h"
#include "drivers/gic_v3.h"

/* TODO: Flesh out driver more */


typedef volatile struct __attribute__((packed)) {
  u32 DCTLR;              /* Distributor Control Reg */
  const u32 DTYPER;       /* Distributor Type Reg*/
  const u32 DIIDR;        /* Distributor Implementation ID Reg*/
  u32 reserved0[29];
  u32 DIGROUPR[32];       /* Distributor Group Reg */
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

/* =========================================================================
 * GIC Distributor Control Register (GICD_CTLR) values
 * ========================================================================= */

#define GIC_GICD_CTLR_DISABLE         (0x00U)
#define GIC_GICD_CTLR_ENABLE          (0x01U)

/* =========================================================================
 * GICD Priority Register macros
 * ========================================================================= */

#define GIC_PRIORITY_HIGHEST          (0x00U)
#define GIC_PRIORITY_LOWEST           (0xF8U)

#define GIC_IPRIORITYR_IRQS_PER_REG      (4U)
#define GIC_IPRIORITYR_BITS_PER_IRQ      (8U)
#define GIC_IPRIORITYR_FIELD_MASK        ((u32)(0xFFUL))

#define IRQ_REG_IPRIORITYR(irq)   ((uint32_t)((irq) / \
                                    GIC_IPRIORITYR_IRQS_PER_REG))
#define IRQ_BIT_IPRIORITYR(irq)   ((uint32_t)((irq) % \
                                    GIC_IPRIORITYR_IRQS_PER_REG) * \
                                    GIC_IPRIORITYR_BITS_PER_IRQ)


/* =========================================================================
 * GIC Trigger Types (used in GICD_ICFGR register)
 * Each IRQ uses 2 bits: 0b10 = edge-triggered, 0b00 = level-triggered
 * ========================================================================= */

#define GIC_TRIGGER_TYPE_MASK   (0x03U)
#define GIC_GICD_ICFGR_LEVEL    (0x0U)   /* level-sensitive */
#define GIC_GICD_ICFGR_EDGE     (0x2U)   /* edge-triggered */
#define GIC_PRI_MASK            (0x0f)

/* =========================================================================
 * GICD_CTLR bits (Distributor control)
 * ========================================================================= */

#define GICD_CTLR_ENABLE_GROUP0       (1U << 0)
#define GICD_CTLR_ENABLE_GROUP1       (1U << 1)

/* =========================================================================
 * Interrupt pending/active/enable/disable field widths
 * ========================================================================= */

#define GIC_BITS_PER_REG              (32U)
#define GICD_ISENABLER_BITS           (GIC_BITS_PER_REG)
#define GICD_ICENABLER_BITS           (GIC_BITS_PER_REG)
#define GICD_IPRIORITYR_BITS          (8U)
#define GICD_ITARGETSR_BITS           (8U)

#define GIC_IRQ_PER_REG (32)
#define IRQ_REG(irq) ((irq) / (GIC_IRQ_PER_REG))
#define IRQ_BIT(irq) ((irq) % (GIC_IRQ_PER_REG))

/* =========================================================================
 * GICD CPU TARGET macros
 * ========================================================================= */

#define GIC_GICD_ITARGETSR_PER_REG      (4)
#define IRQ_REG_ITARGETSR(irq)          ((u32)((irq) / \
                                          GIC_GICD_ITARGETSR_PER_REG))
#define IRQ_BYTE_OFFSET_ITARGETSR(irq)  ((u32)((irq) % \
                                          GIC_GICD_ITARGETSR_PER_REG) * 8U)
#define GIC_ITARGETSR_FIELD_MASK        ((u32)(0xFFUL))

#define GIC_TARGET_CPU0               (0x01U)
#define GIC_TARGET_CPU1               (0x02U)
#define GIC_TARGET_CPU2               (0x04U)
#define GIC_TARGET_CPU3               (0x08U)
#define GIC_TARGET_ALL_CPUS           (0xFFU)

/* =========================================================================
 * GICD Config macros
 * ========================================================================= */

#define GIC_ICFGR_IRQS_PER_REG         (16U)
#define GIC_ICFGR_BITS_PER_IRQ         (2U)

#define IRQ_REG_ICFGR(irq)  ((u32)((irq) / GIC_ICFGR_IRQS_PER_REG))
#define IRQ_BIT_ICFGR(irq)  ((u32)((irq) % GIC_ICFGR_IRQS_PER_REG) * \
                              GIC_ICFGR_BITS_PER_IRQ)
#define GIC_ICFGR_FIELD_MASK           ((u32)(0x03UL)) /* 0x03UL */

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

/* =========================================================================
 * GICC_CTLR bits (CPU interface control)
 * ========================================================================= */

#define GICC_CTLR_ENABLE        (0x1)   /* Enable GICC */
#define GICC_CTLR_DISABLE       (0x0)   /* Disable GICC */
#define GICC_CTLR_ENABLE_GROUP0     (1U << 0)  /* Secure interrupts */
#define GICC_CTLR_ENABLE_GROUP1     (1U << 1)  /* Non-secure interrupts */

/* =========================================================================
 * GICC Priority Mask Register (GICC_PMR)
 * ========================================================================= */

#define GICC_PMR_PRI_MAX            (0xFFU)
#define GICC_PMR_PRI_MIN            (0x00U)  /* Allow all priorities */

/* =========================================================================
 * GICC Priority Mask Register (GICC_PMR)
 * ========================================================================= */

#define GIC_IAR_INTID_MASK    (0x0FFFU)

static gic_distributor_regs *gic_dregs;
static gic_cpu_interface_regs *gic_ifregs;

typedef struct {
  gic_cpu_interface_regs *gic_ifregs_base;
  gic_distributor_regs   *gic_dregs_base;
} gic_plat_config;

/* GIC Private functions */

static dog_status_t gic_enable_clr(irq_no irq) {
  u32 reg = IRQ_REG(irq);
  u32 bit = IRQ_BIT(irq);

  gic_dregs->DICENABLER[reg] = BIT(bit);

  return DOGSTATUS_SUCCESS;
}

static dog_status_t gic_enable_set(irq_no irq) {
  u32 reg = IRQ_REG(irq);
  u32 bit = IRQ_BIT(irq);

  gic_dregs->DISENABLER[reg] = BIT(bit);

  return DOGSTATUS_SUCCESS;
}

static dog_status_t gicd_clear_pending(irq_no irq) {
  u32 reg = IRQ_REG(irq);
  u32 bit = IRQ_BIT(irq);

  gic_dregs->DICPENDR[reg] = BIT(bit);

  return DOGSTATUS_SUCCESS;
}

static dog_status_t gicd_set_target(irq_no irq, u32 cpu_id) {
  u32 reg = IRQ_REG_ITARGETSR(irq);
  u32 bit = IRQ_BYTE_OFFSET_ITARGETSR(irq);

  u32 reg_val = gic_dregs->DITARGETSR[reg];

  /* Clear the 8-bit field corresponding to the IRQ */
  reg_val &= (u32)(~(GIC_ITARGETSR_FIELD_MASK << bit));

  /* Set new CPU target mask */
  reg_val |= (u32)((cpu_id & GIC_ITARGETSR_FIELD_MASK) << bit);

  gic_dregs->DITARGETSR[reg] = reg_val;

  return DOGSTATUS_SUCCESS;
}

static dog_status_t gicd_set_priority(irq_no irq, u32 prio) {
  u32 reg = IRQ_REG_IPRIORITYR(irq);
  u32 bit = IRQ_BIT_IPRIORITYR(irq);

  u32 reg_val = gic_dregs->DIPRIORITY[reg];

  /* Clear existing priority field */
  reg_val &= (u32)~(GIC_IPRIORITYR_FIELD_MASK << bit);

  /* Set new priority */
  reg_val |= (u32)((prio & GIC_IPRIORITYR_FIELD_MASK) << bit);

  gic_dregs->DIPRIORITY[reg] = reg_val;

  return DOGSTATUS_SUCCESS;
}

static dog_status_t gicd_config(irq_no irq, unsigned int config) {
  u32 reg = IRQ_REG_ICFGR(irq);
  u32 bit = IRQ_BIT_ICFGR(irq);

  u32 reg_val = gic_dregs->DICFGR[reg];

  /* Clear existing 2-bit config field */
  reg_val &= (u32)(~(GIC_ICFGR_FIELD_MASK << bit));

  /* Set new trigger configuration (level or edge) */
  reg_val |= (u32)((config & GIC_ICFGR_FIELD_MASK) << bit);

  gic_dregs->DICFGR[reg] = reg_val;

  return DOGSTATUS_SUCCESS;
}

static dog_status_t init_gicc(void) {
  gic_ifregs->CCPMR = GICC_PMR_PRI_MAX;
  gic_ifregs->CCLTR = GICC_CTLR_ENABLE;

  return DOGSTATUS_SUCCESS;
}

static dog_status_t init_gicd(void) {
  gic_dregs->DCTLR = GIC_GICD_CTLR_DISABLE;
  gic_dregs->DCTLR  = GIC_GICD_CTLR_ENABLE;

  return DOGSTATUS_SUCCESS;
}

static dog_status_t gic_init(gic_plat_config *gic_config) {
  dog_status_t status = DOGSTATUS_SUCCESS;

  if ((gic_config == NULL) ||
      (gic_config->gic_dregs_base == NULL) ||
      (gic_config->gic_ifregs_base  == NULL)) {
    status = DOGSTATUS_INVALID_PARAM;
  } else {
    gic_dregs = gic_config->gic_dregs_base;
    gic_ifregs = gic_config->gic_ifregs_base;

    status = init_gicd();
    if (status == DOGSTATUS_SUCCESS) {
      status = init_gicc();
    }
  }

  return status;
}

/* GIC Public functions */

u16 gicc_acknowledge_int(void) {
  return (u16)(gic_ifregs->CIAR & GIC_IAR_INTID_MASK);
}

void gic_eoi(irq_no irq) {
  gic_ifregs->CEOIR = irq;

  return;
}

dog_status_t gic_unregister_int(irq_no irq) {
  dog_status_t status = gic_enable_clr(irq);

  return status;
}

dog_status_t gic_register_int(irq_no irq) {
  dog_status_t status = DOGSTATUS_SUCCESS;

  if (gicd_config(irq, GIC_GICD_ICFGR_EDGE) != DOGSTATUS_SUCCESS) {
        status = DOGSTATUS_ERROR;
  }

  if (status == DOGSTATUS_SUCCESS) {
    if (gicd_set_priority(irq, GIC_PRIORITY_HIGHEST) != DOGSTATUS_SUCCESS) {
      status = DOGSTATUS_ERROR;
    }
  }

  if (status == DOGSTATUS_SUCCESS) {
    if (gicd_set_target(irq, GIC_TARGET_CPU0) != DOGSTATUS_SUCCESS) {
      status = DOGSTATUS_ERROR;
    }
  }

  if (status == DOGSTATUS_SUCCESS) {
    if (gicd_clear_pending(irq) != DOGSTATUS_SUCCESS) {
      status = DOGSTATUS_ERROR;
    }
  }

  if (status == DOGSTATUS_SUCCESS) {
    if (gic_enable_set(irq) != DOGSTATUS_SUCCESS) {
      status = DOGSTATUS_ERROR;
    }
  }

  return status;
}

dog_status_t gic_probe(dt_node_info *gic_node_info) {
  static gic_plat_config plat_gic_config = {
    .gic_ifregs_base = 0,
    .gic_dregs_base = 0
  };

  plat_gic_config.gic_dregs_base =
        (gic_distributor_regs *)gic_node_info->regs[0].addr;
  plat_gic_config.gic_ifregs_base =
        (gic_cpu_interface_regs *)gic_node_info->regs[1].addr;

  dog_status_t status = gic_init(&plat_gic_config);

  return status;
}
