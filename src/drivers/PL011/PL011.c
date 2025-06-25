#include "types.h"
#include "drivers.h"
#include "stddef.h"
#include "libs/dogprint.h"
#include "drivers/PL011.h"
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


/* =========================================================================
 * PL011 UART - Control Register (CR)
 * =========================================================================
 * Address offset: 0x30
 *
 * Bit(s) | Name      | Description
 * -------|-----------|---------------------------------------------------
 *  [0]   | UARTEN    | UART Enable (1 = enable, 0 = disable)
 *  [1]   | SIREN     | SIR (IrDA) Enable
 *  [2]   | SIRLP     | SIR Low Power Mode
 *  [8]   | TXE       | Transmit Enable
 *  [9]   | RXE       | Receive Enable
 *  [10]  | DTR       | Data Transmit Ready
 *  [11]  | RTS       | Request To Send
 *  [12]  | Out1      | User-defined OUT1
 *  [13]  | Out2      | User-defined OUT2
 *  [14]  | RTSEn     | RTS hardware flow control enable
 *  [15]  | CTSEn     | CTS hardware flow control enable
 * =========================================================================
*/

#define PL011_CR_UARTEN_POS     ((u32)0U)
#define PL011_CR_UARTEN_MASK    ((u32)1U << PL011_CR_UARTEN_POS)
#define PL011_CR_UARTEN_ENABLE  ((u32)1U << PL011_CR_UARTEN_POS)

#define PL011_CR_TXE_POS        ((u32)8U)
#define PL011_CR_TXE_MASK       ((u32)1U << PL011_CR_TXE_POS)
#define PL011_CR_TXE_ENABLE     ((u32)1U << PL011_CR_TXE_POS)

#define PL011_CR_RXE_POS        ((u32)9U)
#define PL011_CR_RXE_MASK       ((u32)1U << PL011_CR_RXE_POS)
#define PL011_CR_RXE_ENABLE     ((u32)1U << PL011_CR_RXE_POS)

/* Combined config */
#define PL011_CR_ENABLE_TX_RX   (PL011_CR_UARTEN_ENABLE | \
                                 PL011_CR_TXE_ENABLE | PL011_CR_RXE_ENABLE)

/* =========================================================================
 * PL011 UART - Interrupt Clear Register (ICR)
 * =========================================================================
 * Address offset: 0x44
 *
 * Writing '1' to a bit clears the corresponding interrupt.
 * Bit(s) | Name       | Description
 * -------|------------|-----------------------------------------------
 *  [10:0]| ALL IRQs   | Writing 0x7FF clears all documented IRQs
 * =========================================================================
 */

#define PL011_ICR_ALL           ((u32)0x7FFU)

/* =========================================================================
 * PL011 UART - Line Control Register (LCRH)
 * =========================================================================
 * Address offset: 0x2C
 *
 * Bit(s) | Name    | Description
 * -------|---------|---------------------------------------------------
 *  [0]   | BRK     | Send break (forces TX low)
 *  [1]   | PEN     | Parity enable
 *  [2]   | EPS     | Even parity select
 *  [3]   | STP2    | Two stop bits (1 = 2 stop bits)
 *  [4]   | FEN     | Enable FIFOs (1 = enabled)
 *  [5:6] | WLEN    | Word length:
 *         | 0b00 = 5 bits
 *         | 0b01 = 6 bits
 *         | 0b10 = 7 bits
 *         | 0b11 = 8 bits
 *  [7]   | SPS     | Stick parity select
 * =========================================================================
 */

#define PL011_LCRH_WLEN_POS     ((u32)5U)
#define PL011_LCRH_WLEN_MASK    ((u32)0x3U << PL011_LCRH_WLEN_POS)
#define PL011_LCRH_WLEN_8BIT    ((u32)0x3U << PL011_LCRH_WLEN_POS)

#define PL011_LCRH_FEN_POS      ((u32)4U)
#define PL011_LCRH_FEN_MASK     ((u32)1U << PL011_LCRH_FEN_POS)
#define PL011_LCRH_FEN_ENABLE   ((u32)1U << PL011_LCRH_FEN_POS)

/* Combined config: 8 data bits, 1 stop bit, FIFO enabled */
#define PL011_LCRH_8N1_FEN      (PL011_LCRH_WLEN_8BIT | PL011_LCRH_FEN_ENABLE)

/* =========================================================================
 * PL011 UART - Flag Register (FR)
 * =========================================================================
 * Address offset: 0x18 (read-only)
 *
 * Bit(s) | Name    | Description
 * -------|---------|---------------------------------------------------
 *  [0]   | CTS     | Clear to send
 *  [3]   | BUSY    | UART is busy transmitting or receiving
 *  [4]   | RXFE    | Receive FIFO empty
 *  [5]   | TXFF    | Transmit FIFO full
 *  [6]   | RXFF    | Receive FIFO full
 *  [7]   | TXFE    | Transmit FIFO empty
 * =========================================================================
 */

#define PL011_FR_TXFE_POS       ((u32)7U)
#define PL011_FR_TXFE_MASK      ((u32)1U << PL011_FR_TXFE_POS)

#define PL011_FR_RXFF_POS       ((u32)6U)
#define PL011_FR_RXFF_MASK      ((u32)1U << PL011_FR_RXFF_POS)

#define PL011_FR_TXFF_POS       ((u32)5U)
#define PL011_FR_TXFF_MASK      ((u32)1U << PL011_FR_TXFF_POS)

#define PL011_FR_RXFE_POS       ((u32)4U)
#define PL011_FR_RXFE_MASK      ((u32)1U << PL011_FR_RXFE_POS)

#define PL011_FR_BUSY_POS       ((u32)3U)
#define PL011_FR_BUSY_MASK      ((u32)1U << PL011_FR_BUSY_POS)

#define PL011_FR_CTS_POS        ((u32)0U)
#define PL011_FR_CTS_MASK       ((u32)1U << PL011_FR_CTS_POS)

static struct dogconsole pl011_con;

static dog_status_t pl011_putc(const char c) {
  pl011_registers *uart = (pl011_registers *)pl011_con.base_addr;

  /* wait until we can send */
  do {
      asm volatile("nop");
  } while ((uart->FR & PL011_FR_TXFF_MASK) != 0U);
  /* write the character to the buffer */
  uart->DR = (unsigned int)c;

  return DOGSTATUS_SUCCESS;
}

static dog_status_t pl011_init(pl011_registers *uart) {
  uart->CR = 0U;                                /* Disable UART */
  uart->ICR = PL011_ICR_ALL;                    /* Clear interrupts */
  uart->LCRH = PL011_LCRH_8N1_FEN;              /* 8-bit, 1-stop, FIFO */
  uart->CR = PL011_CR_ENABLE_TX_RX;             /* Enable UART, TX, RX */

  return DOGSTATUS_SUCCESS;
}

/* TODO: Setup AMBA driver to probe for precense of device
 *  for now we assume its there */
dog_status_t pl011_probe(dt_node_info *pl011_node_info) {
  pl011_registers *regs = (pl011_registers *)pl011_node_info->regs[0].addr;
  dog_status_t status = pl011_init(regs);

  if (status == DOGSTATUS_SUCCESS) {
    pl011_con.base_addr = pl011_node_info->regs[0].addr;
    pl011_con.putc = pl011_putc;

    register_console(&pl011_con);
  }

  return status;
}
