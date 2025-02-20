#include "dogprint_proto.h"
#include "types.h"

void dogprint_init(console *console_base) {
  stdoutdog = console_base;

  return;
}

int dogprint(u8 *str) {
  u8 *c = str;

  while (*c != '\0') {
    if (putc(*c) == 0)
      c++;
    else
      return -1;
  }

  return 0;
}

#define MAX_NUM_SIZE 8
int dogprintnum(u64 x) {
  u8 a;
  u8 c;
  int index = 0;
  u8 buf[MAX_NUM_SIZE];

  dogprint((u8 *)"0x");

  // num is zero detect and write zero
  if (x == 0) {
    putc('0');
    dogprint((u8 *)"\r\n");
    return 0;
  }

  while (x > 0) {
    // get digit for place
    a = x % 16;

    // convert to hexadecimal value
    if (a < 10)
      c = a + 0x30;
    else
      c = a + 0x41 - 10;

    // fill buf from front to back
    buf[index++] = c;
    x = x /16;
  }

  // print each digit backwards to get correct endianess
  while (index >= 0) {
    c = buf[index--];
    putc(c);
  }

  dogprint((u8 *)"\r\n");

  return 0;
}

int putc(const u8 c) {
  return plat_putc(stdoutdog, (unsigned int)c);
}
