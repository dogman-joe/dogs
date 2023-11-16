//LED
#define GPIO1_BASE              0x4804C000
#define GPIO1_OE                (GPIO1_BASE+0x134)
#define GPIO1_CLEARDATAOUT      (GPIO1_BASE+0x190)
#define GPIO1_SETDATAOUT        (GPIO1_BASE+0x194)
#define CM_PER_BASE             0x44E00000
#define CM_PER_L4LS_CLKCTRL       (CM_PER_BASE+0x00)
#define CM_PER_GPIO1_CLKCTRL    (CM_PER_BASE+0xAC)
#define CM_PER_TIMER2_CLKCTRL (CM_PER_BASE+0x80)

extern void dummy();
extern void PUT32 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );

void early_debug_light_led()
{
  int led = 1 << 21;

  PUT32(GPIO1_SETDATAOUT,led);

  return;
}

void early_debug_light_led2()
{
  int led = 2 << 21;

  PUT32(GPIO1_SETDATAOUT,led);

  return;
}

void early_debug_light_led3()
{
  int led = 4 << 21;

  PUT32(GPIO1_SETDATAOUT,led);

  return;
}

void dogpio_init()
{
  /* Wake up GPIO1 Clk */
   PUT32(CM_PER_GPIO1_CLKCTRL,2);

   while(1)
    {
      if((GET32(CM_PER_GPIO1_CLKCTRL)&0x00030000)==0) break;
    }

  /*enable output for pin*/
  PUT32(GPIO1_OE,0xFE1FFFFF);

  return;
}
