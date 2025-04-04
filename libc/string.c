#include "string.h"

void *memset(void *dest, register uint8_t val, register size_t len) {
  register unsigned char *ptr = (unsigned char*)dest;

  while (len-- > 0) {
    *ptr++ = val;
  }

  return dest;
}


void *memcpy(void *dest, void *src, register size_t len) {
  register unsigned char *dptr = (unsigned char*)dest;
  register unsigned char *sptr = (unsigned char*)src;

  while (len-- > 0) {
    *dptr++ = *sptr++;
  }

  return dest;
}

int strlen(char *s) {
  size_t len = 0;

  while (*s != '\0') {
    len++;
    s++;
  }

  return len;
}

int strcmp(const char *s1, const char *s2) {
  while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
    s1++;
    s2++;
  }

  return (*s1 - *s2);
}

int strncmp(const char *s1, const char *s2, uint32_t len) {
  while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2 && len--) {
    s1++;
    s2++;
  }

  return len;
}
