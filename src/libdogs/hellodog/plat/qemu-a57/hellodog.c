#include "types.h"
#include "libs/dogprint.h"

void process(u32 num) {
  u32 a = 0;

  while (1) {
    for (int i = 0; i < 0xFFFFFF; i++)
      a++;
    for (int i = 0; i < num + 1; i++)
      dogprint("proc");

    dogprint("\r\n");
  }

  return;
}
