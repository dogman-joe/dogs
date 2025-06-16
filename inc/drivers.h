#ifndef DRIVERS_H_
#define DRIVERS_H_
/* Driver Table */

#include "stdint.h"

typedef struct {
    uintptr_t addr;
    size_t size;
} dt_reg;

typedef struct {
  dt_reg regs[4];
} dt_node_info;

typedef struct {
  char name[0x20];
  int (*probe)(dt_node_info *);
} driver_table_info;



#endif   /* DRIVERS_H_ */
