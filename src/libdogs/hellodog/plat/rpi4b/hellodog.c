#include "types.h"
#include "libs/dogprint.h"

void process(u32 num) {
  int a;

  while (1) {
    for (int i = 0; i < 0xfffffff; i++)
      a++;
    for (int i = 0; i < num + 1; i++)
      dogprint("proc");

    dogprint("\r\n");
  }

  return;
}

