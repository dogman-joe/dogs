#ifndef CPU_H_
#define CPU_H_

#include "types.h"

#define MRS(reg, v)  asm volatile("mrs %x0," reg : "=r"(v))
#define MSR(reg, v)  asm volatile("msr " reg ",%x0" : "=r"(v))

/* Generic Timer */

#define CNTV_CTL_EL0    "cntv_ctl_el0"
/* CNTV_CTL_EL0, Counter-timer Virtual Timer Control register
 * Control register for the virtual timer
 * ISTATUS, bit [2]:    The status of the timer interrupt
 * IMASK, bit [1]:      Timer interrupt mask bit
 * ENABLE, bit [0]:     Enables the timer
 */

#define CNTFRQ_EL0 "cntfrq_el0"
/* CNTFRQ_EL0, Counter-timer Frequency register */

#define CNTVCT_EL0 "cntvct_el0"
/* CNTVCT_EL0, Counter-timer Virtual Count register
 * Holds the 64-bit virtual count value
 */

#define CNTV_CVAL_EL0 "cntv_cval_el0"
/* CNTV_CVAL_EL0, Counter-timer Virtual Timer CompareValue register
 * Holds the compare value for the virtual timer
 */

#define CNTV_CTL_ENABLE      (1 << 0)   /* Enables the timer */
#define CNTV_CTL_IMASK       (1 << 1)   /* Timer interrupt mask bit */
#define CNTV_CTL_ISTATUS     (1 << 2)   /* The status of the timer interrupt */

/* CNTV_CTL_EL0, Counter-timer Virtual Timer Control register
 * Control register for the virtual timer
 * ISTATUS, bit [2]:    The status of the timer interrupt
 * IMASK, bit [1]:      Timer interrupt mask bit
 * ENABLE, bit [0]:     Enables the timer
*/

u32 get_cntv_ctl(void) {
  u32 reg_val;

  MRS(CNTV_CTL_EL0, reg_val);

  return reg_val;
}

void disable_cntv(void) {
  u32 reg_val;

  reg_val = get_cntv_ctl();
  reg_val &= ~CNTV_CTL_ENABLE;

  MSR(CNTV_CTL_EL0, reg_val);

  return;
}

void enable_cntv(void) {
  u32 reg_val;

  reg_val = get_cntv_ctl();
  reg_val |= CNTV_CTL_ENABLE;

  MSR(CNTV_CTL_EL0, reg_val);

  return;
}

u32 get_cntfrq_el0(void) {
  u32 reg_val;

  MRS(CNTFRQ_EL0, reg_val);

  return reg_val;
}

void put_cntfrq_el0(u32 reg_val) {
  MSR(CNTFRQ_EL0, reg_val);

  return;
}

u64 get_cntvct_el0(void) {
  u64 reg_val;

  MRS(CNTVCT_EL0, reg_val);

  return reg_val;
}

u64 get_cntv_cval_el0(void) {
  u64 reg_val;

  MRS(CNTV_CVAL_EL0, reg_val);

  return reg_val;
}

void put_cntv_cval_el0(u64 reg_val) {
  MSR(CNTV_CVAL_EL0, reg_val);

  return;
}

#endif   /* CPU_H_ */
