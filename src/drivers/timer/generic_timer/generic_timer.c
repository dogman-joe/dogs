#include "types.h"
#include "arch/armv8-a/cpu.h"

#define TIMER_WAIT 1
#define GENERIC_TIMER_INT_NO 27

/* TODO: Flesh out driver more */
extern void gic_register_int(u32 irq_no);
extern u32 cntfrq;

void generic_timer_handle() {
  disable_cntv();

  u64 ticks = TIMER_WAIT * cntfrq;
  u64 current_cnt = get_cntvct_el0();

  put_cntv_cval_el0(current_cnt + ticks);
  enable_cntv();

  return;
}

void generic_timer_init() {
  disable_cntv();

  cntfrq = get_cntfrq_el0();

  /* Next timer IRQ is after n sec(s) */
  u32 ticks = 1 * cntfrq;
  u32 current_cnt = get_cntvct_el0();
  put_cntv_cval_el0(current_cnt + ticks);

  /* register interrupt for generic timer */
  gic_register_int(GENERIC_TIMER_INT_NO);

  enable_cntv();

  return;
}

