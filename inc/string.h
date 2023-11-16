#ifndef _STRING_H
#define _STRING_H

#include "types.h"


void *memset (void *dest, register u32 val, register size_t len)
{
  register unsigned char *ptr = (unsigned char*)dest;
  while (len-- > 0)
    *ptr++ = val;

  return dest;
}

#endif   /* _STRING_H */
