#ifndef DOGPRINT_PROTO_H_
#define DOGPRINT_PROTO_H_

#include "types.h"

int putc(const u8 c);

extern int plat_uart_putc(const u8 c);

#endif  /*DOGPRINT_PROTO_H_*/
