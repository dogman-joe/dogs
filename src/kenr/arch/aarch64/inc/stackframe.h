#ifndef STACKFRAME_H_
#define STACKFRAME_H_

#include "types.h"

typedef u64 reg_t; /* machine register */

struct stackframe_t {
  reg_t x19;
  reg_t x20;
  reg_t x21;
  reg_t x22;
  reg_t x23;
  reg_t x24;
  reg_t x25;
  reg_t x26;
  reg_t x27;
  reg_t x28;
  reg_t fp;
  reg_t sp;
  reg_t lr;
  reg_t xzr;
};

#endif /* STACKFRAME_H_ */
