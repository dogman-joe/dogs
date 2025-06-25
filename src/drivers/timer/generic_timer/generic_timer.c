#include "types.h"
#include "arch/armv8-a/cpu.h"
#include "drivers/gic_v3.h"
#include "drivers/generic_timer.h"

#define TIMER_WAIT ((u32)1UL)
#define GENERIC_TIMER_INT_NO (27U)

/* TODO: Flesh out driver more */
static u32 cntfrq;

/* Generic Timer Private functions */

void generic_timer_handle(void) {
  disable_cntv();

  u32 ticks = TIMER_WAIT * cntfrq;
  u64 current_cnt = get_cntvct_el0();

  put_cntv_cval_el0(current_cnt + ticks);
  enable_cntv();

  return;
}

/* Generic Timer Public functions */

dog_status_t generic_timer_init(void) {
  disable_cntv();

  cntfrq = get_cntfrq_el0();

  /* Next timer IRQ is after n sec(s) */
  u32 ticks = TIMER_WAIT * cntfrq;
  u32 current_cnt = get_cntvct_el0();
  put_cntv_cval_el0(current_cnt + ticks);

  /* register interrupt for generic timer */
  dog_status_t status = gic_register_int(GENERIC_TIMER_INT_NO);

  if (status == DOGSTATUS_SUCCESS) {
    enable_cntv();
  }

  return status;
}

