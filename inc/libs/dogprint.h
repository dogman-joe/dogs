#ifndef DOGPRINT_H_
#define DOGPRINT_H_

#include "stdint.h"

struct dogconsole {
  uintptr_t base_addr;
  int (*putc)(const char);
};

void register_console(struct dogconsole *con);

int dogprint(char *s);
int dogprintnum(u32 x);
int dogprintnum64(u64 x);

#endif  /*DOGPRINT_H_*/

