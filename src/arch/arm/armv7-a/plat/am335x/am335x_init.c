#include "plat_proto.h"
#include "types.h"

void plat_start_dogtime() {
  plat_timer_start();

  return;
}

void plat_init() {
  plat_timer_init();

  return;
}


