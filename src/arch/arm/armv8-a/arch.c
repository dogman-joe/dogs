#include "arch/arch.h"
#include "stdint.h"
#include "stddef.h"
#include "stdbool.h"
#include "string.h"
#include "plat_proto.h"
#include "stackframe.h"
#include "drivers.h"
#include "libs/hello.h"
#include "cpu_arch.h"
#include "drivers/gic_v3.h"
#include "drivers/generic_timer.h"
#include "drivers/PL011.h"
#include "libs/dogtb.h"
#include "libs/dogprint.h"

/* Drivers Table names */
#define GIC_400_NAME "arm,gic-400"
#define GIC_A15_NAME "arm,cortex-a15-gic"
#define PL011_NAME "arm,pl011"


/* arch Private variables */

extern reg_t stack_top;

/* arch Private functions */
static void arch_console_init(void) {
  /* TODO: figure this weird shit out bro */
  const driver_table_info console_driver_table[2] = {
    {
      .name = PL011_NAME,
      .probe = pl011_probe
    },
  };

  u32 num_drivers = sizeof(console_driver_table) / sizeof(driver_table_info);

  for (u32 i = 0; i < num_drivers; i++) {
    dt_node_info *node_ptr = find_compatible(GET_DTB_PTR(),
    console_driver_table[i].name);

    if (node_ptr != NULL) {
      /* probe and init console */
      dog_status_t status = console_driver_table[i].probe(node_ptr);

      if (status != DOGSTATUS_SUCCESS) {
        /* TODO: add log to log failure */
      }
    }
  }

  return;
}

/* arch Public function */

void arch_dogproc_init(struct stackframe_t *dog, int entry) {
  dog->lr = (reg_t)dog_spawn;
  dog->x19 = (reg_t)process;
  dog->x20 = (reg_t)entry;

  /* for now we use root tasks sp at static location
   *  TODO: change this to be dynamic */
  dog->sp = (reg_t)(&stack_top + ((entry + 1) * 0x4000));

  return;
}

dog_status_t arch_start_dogtime(void) {
  /* aarch64 arch uses generic timer for global clock */
  dog_status_t status  = generic_timer_init();

  return status;
}

void arch_handle_irq(void) {
  u16 irq_no = gicc_acknowledge_int();

  /* handle pending irq if generic timer use our dogtick function */
  if (irq_no == GENERIC_TIMER_IRQ_NO) {
    irq_handle(0);
  } else {
    irq_handle(irq_no);
  }

  return;
}

void arch_clock_irq_handle(void) {
  /* handle generic timer interrupt after firing */
  generic_timer_handle();
  gic_eoi(GENERIC_TIMER_IRQ_NO);

  return;
}

void arch_irq_init(void) {
  static const driver_table_info intc_driver_table[2] = {
    {
      .name = GIC_A15_NAME,
      .probe = gic_probe
    },
    {
      .name = GIC_400_NAME,
      .probe = gic_probe
    }
  };

  u32 num_drivers = sizeof(intc_driver_table) / sizeof(driver_table_info);
  bool initialized = false;

  for (u32 i = 0; i < num_drivers; i++) {
    dt_node_info *node_ptr = find_compatible(GET_DTB_PTR(),
      intc_driver_table[i].name);

      if (node_ptr != NULL) {
        dog_status_t status = gic_probe(node_ptr);

        if (status != DOGSTATUS_SUCCESS) {
          initialized = false;
          dogprint("failed to probe interrupt controller!!\r\n");
        } else {
          initialized = true;
          dogprint("interrupt controller probe success\r\n");
        }
      }
  }

  if (initialized == false) {
    dogprint("failed to init a interrupt controller!!\r\n");
  } else {
    /* init gic_v3 */
    dogprint("initialized GIC\r\n");

    /* unmask IRQ bit in DAIF */
    enable_irq();
    dogprint("unmasked I in DAIF\r\n");
  }

  return;
}

void arch_init(void) {
  /* set up exeception vector table */
  write_vbar();

  /* init OS console output */
  arch_console_init();

  return;
}
