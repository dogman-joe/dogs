#ifndef STACKFRAME_H_
#define STACKFRAME_H_

#include "types.h"

typedef u32 reg_t;         /* machine register */

struct stackframe_t {
  reg_t r0;
  reg_t r1;
  reg_t r2;
  reg_t r3;
  reg_t r4;
  reg_t r5;
  reg_t r6;
  reg_t r7;
  reg_t r8;
  reg_t r9;   /*  sb */
  reg_t r10;  /*  sl */
  reg_t fp;   /*  r11 */
  reg_t r12;  /*  ip */
  reg_t sp;   /*  r13 */
  reg_t lr;   /*  r14 */
  reg_t psr;
};

#endif /* STACKFRAME_H_*/
