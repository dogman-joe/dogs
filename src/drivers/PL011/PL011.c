#include "types.h"
#include "drivers.h"
#include "arch/armv8-a/io.h"

/* TODO: Flesh out driver more */

/* PL011 UART registers */

typedef volatile struct __attribute__((packed)) {
        u32 DR;                 /* 0x0 Data Register */
        u32 RSRECR;             /* 0x4 Receive status / error clear register */
        u32 _reserved0[4];      /* 0x8 - 0x14 reserved */
        const u32 FR;           /* 0x18 Flag register */
        u32 _reserved1;         /* 0x1C reserved */
        u32 ILPR;               /* 0x20 Low-power counter register */
        u32 IBRD;               /* 0x24 Integer baudrate register */
        u32 FBRD;               /* 0x28 Fractional baudrate register */
        u32 LCRH;               /* 0x2C Line control register */
        u32 CR;                 /* 0x30 Control register */
        u32 IFLS;               /* 0x34 Interrupt FIFO level select register */
        u32 IMSC;               /* 0x38 Interrupt Mask set/clear register */
        u32 RIS;                /* 0x3c Raw Interrupt Status register */
        u32 MIS;                /* 0x40 Masked Interrupt Status register */
        u32 ICR;                /* 0x44 Interrupt Clear register */
        u32 DMACR;              /* 0x48 DMA control register */
} pl011_registers;


int plat_putc(pl011_registers *uart, unsigned int c) {
  // wait until we can send
  do {
      asm volatile("nop");
  } while (uart->FR&0x20);
  // write the character to the buffer
  uart->DR = c;

  return 0;
}

void pl011_init(pl011_registers *uart) {
  uart->CR = 0;
  /* clear interrupts */
  uart->ICR = 0x7FF;
  /* 8 data bits 1 stop bit */
  uart->LCRH = 0b11 << 5;
  /* enable TX RX FIFO */
  uart-> CR = 0x301;

  return;
}

/* TODO: Setup AMBA driver to probe for precense of device
 *  for now we assume its there */
int pl011_probe(dt_node_info *pl011_node_info) {
  pl011_init((pl011_registers *)pl011_node_info->reg_vals[0]);

  return 0;
}
