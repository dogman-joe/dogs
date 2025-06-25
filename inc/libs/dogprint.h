#ifndef DOGPRINT_H_
#define DOGPRINT_H_

#include "types.h"
#include "stdint.h"

struct dogconsole {
  uintptr_t base_addr;
  dog_status_t (*putc)(const char);
};

void register_console(struct dogconsole *con);

void dogprint(const char *s);
void dogprintnum(u32 x);
void dogprintnum64(u64 x);

#endif  /*DOGPRINT_H_*/

