#include "types.h"

extern int dogprint(char *c);

void process(u32 num) {
  int a = 0;

  while (1) {
    for (int i = 0; i < 0x80000; i++)
      a++;
    for (int i = 0; i < num + 1; i++)
      dogprint("proc");
      
    dogprint("\r\n");
  }

  return;
}

