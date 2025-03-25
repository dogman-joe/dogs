#include "dogprint_proto.h"
#include "types.h"

void dogprint_init(console *console_base) {
  stdoutdog = console_base;

  return;
}

int dogprint(char *str) {
  char *c = str;

  while (*c != '\0') {
    if (putc(*c) == 0)
      c++;
    else
      return -1;
  }

  return 0;
}

char hex_digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
  'a', 'b', 'c', 'd', 'e', 'f'};

int dogprintnum64(u64 x) {
  u8 a;
  u8 c;

  dogprint("0x");

  for (int i = 0x14; i >=0; i--) {
    // get digit for place
    a = (x >> (i * 4)) & 0x0F;

    c = hex_digits[a];
    putc(c);
  }

  dogprint("\r\n");

  return 0;
}

int dogprintnum(u32 x) {
  u8 a;
  u8 c;

  dogprint("0x");

  for (int i = 7; i >=0; i--) {
    // get digit for place
    a = (x >> (i * 4)) & 0x0F;

    c = hex_digits[a];
    putc(c);
  }

  dogprint("\r\n");

  return 0;
}

int putc(const char c) {
  return plat_putc(stdoutdog, (unsigned int)c);
}
