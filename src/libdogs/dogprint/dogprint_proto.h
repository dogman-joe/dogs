#ifndef DOGPRINT_PROTO_H_
#define DOGPRINT_PROTO_H_

#include "types.h"
typedef u64 console;

console *stdoutdog;

int plat_putc(console *console_base, const u8 c);

#endif  /*DOGPRINT_PROTO_H_*/
