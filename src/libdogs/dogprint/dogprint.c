#include "dogprint_proto.h"
#include "libs/dogprint.h"
#include "stdint.h"
#include "stddef.h"

static struct dogconsole *active_console = NULL;

int putc(const char c) {
  active_console->putc(c);
  return 0;
}

void register_console(struct dogconsole *con) {
  active_console = con;
}

int dogprintbyte(uint8_t byte) {
  const char hex_chars[] = "0123456789ABCDEF";
  putc(hex_chars[(byte >> 4) & 0xF]);  /* high nibble */
  putc(hex_chars[byte & 0xF]);         /* low nibble */

  return 0;
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
  dogprint("0x");

  int started = 0;
  for (int i = 60; i >= 0; i -= 4) {
    uint8_t nibble = (x >> i) & 0xF;
    if (nibble || started || i == 0) {
      putc(hex_digits[nibble]);
      started = 1;
    }
  }

  dogprint("\r\n");

  return 0;
}

int dogprintnum(u32 x) {
  dogprint("0x");

  int started = 0;
  for (int i = 28; i >= 0; i -= 4) {
    uint8_t nibble = (x >> i) & 0xF;
    if (nibble || started || i == 0) {
      putc(hex_digits[nibble]);
      started = 1;
    }
  }

  dogprint("\r\n");

  return 0;
}


