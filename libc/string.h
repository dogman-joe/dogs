#ifndef STRING_H_
#define STRING_H_

#include "stdint.h"


void *memset(void *dest, register uint8_t val, register size_t len);

void *memcpy(void *dest, void *src, register size_t len);

int strlen(char *s);

int strcmp(const char *s, const char *t);

int strncmp(const char *s, const char *t, uint32_t len);
#endif   /* STRING_H_ */
