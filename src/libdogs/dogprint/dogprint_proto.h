#ifndef DOGPRINT_PROTO_H_
#define DOGPRINT_PROTO_H_

#include "types.h"

int putc(const u8 c);

typedef u64 console;

console *stdoutdog;

extern int plat_putc(console *console_base, const u8 c);

#endif  /*DOGPRINT_PROTO_H_*/
