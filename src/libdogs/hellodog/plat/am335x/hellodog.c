#include "types.h"
#include "arch/armv7-a/io.h"

// LED
#define GPIO1_BASE              0x4804C000
#define GPIO1_OE                (GPIO1_BASE+0x134)
#define GPIO1_CLEARDATAOUT      (GPIO1_BASE+0x190)
#define GPIO1_SETDATAOUT        (GPIO1_BASE+0x194)
#define CM_PER_BASE             0x44E00000
#define CM_PER_L4LS_CLKCTRL       (CM_PER_BASE+0x00)
#define CM_PER_GPIO1_CLKCTRL    (CM_PER_BASE+0xAC)
#define CM_PER_TIMER2_CLKCTRL (CM_PER_BASE+0x80)

extern void dummy(void);

int inited = 0;

void led_init() {
  inited = 1;
  /* Wake up GPIO1 Clk */
  PUT32(CM_PER_GPIO1_CLKCTRL, 2);

  while (1) {
    if ((GET32(CM_PER_GPIO1_CLKCTRL) & 0x00030000) == 0)
      break;
  }

  /*enable output for pin*/
  PUT32(GPIO1_OE, 0xFE1FFFFF);

  return;
}


void hello(unsigned int led) {
  if (!inited)
    led_init();

  int a = 0;
  int b = 0;

  /* map led int to led GPIO register bits */
  led = led % 4;
  led = 1 << led;
  led = led << 21;

  while (1) {
    PUT32(GPIO1_SETDATAOUT, led);

    for (int i = 0; i < 0x80000; i++) {
      a++;
    }

    PUT32(GPIO1_CLEARDATAOUT, led);

    for (int i = 0; i < 0x80000; i++) {
      b++;
    }

     a = a + b;
     b = a - b;
  }

  return;
}
