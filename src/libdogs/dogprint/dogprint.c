#include "dogprint_proto.h"

void init_dogprint() {
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

int dogprintnum(int x) {
  int a;
  char c;

  dogprint("0x");
  while (x > 0) {
    a = x % 16;

    if (a < 10)
      c = a + 0x30;
    else
      c = a + 0x41;

    putc(c);
    x = x /16;
  }

  dogprint("0");

  return 0;
}

int putc(const u8 c) {
  return plat_uart_putc(c);
}
