#include "string.h"

void *memset(void *dest, register u32 val, register size_t len) {
  register unsigned char *ptr = (unsigned char*)dest;
  while (len-- > 0)
    *ptr++ = val;

  return dest;
}

