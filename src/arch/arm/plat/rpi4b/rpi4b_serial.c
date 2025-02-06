#include "plat_proto.h"
#include "rpi4b_aux.h"

struct rpi4b_aux *aux_base;
struct rpi4b_aux_mini *mini_base;

int plat_uart_putc(const u8 c) {
  while (1) {
    if (mini_base->MU_LSR & 0x20)
      break;
  }
  mini_base->MU_IO[0] =  c;

  return 0;
}

void plat_muart_gpio_init() {
  int gpio_sel;

  gpio_sel = GET32(GPFSEL1);
  gpio_sel &= GPIO14_MASK;
  gpio_sel |= ALT5_MASK << GPIO14_SHIFT;
  gpio_sel &= GPIO15_MASK;
  gpio_sel |= ALT5_MASK << GPIO15_SHIFT;
  PUT32(GPFSEL1, gpio_sel);
  PUT32(GPPUD, 0);

  for (int i=0; i<150; i++)
    dummy();

  return;
}

void plat_muart_init() {
  aux_base = (struct rpi4b_aux *)AUX_BASE;
  mini_base = (struct rpi4b_aux_mini *)MINI_BASE;

  aux_base->AUX_ENABLES = 1;

  mini_base->MU_IER =  0;
  mini_base->MU_CNTL = 0;
  mini_base->MU_LCR =  3;
  mini_base->MU_MCR =  0;
  mini_base->MU_IER =  0;
  mini_base->MU_BAUD = AUX_MU_BAUD(115200);

  plat_muart_gpio_init();

  mini_base->MU_CNTL = 3;

  return;
}
