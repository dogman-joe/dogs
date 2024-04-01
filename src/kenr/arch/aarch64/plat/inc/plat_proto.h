#ifndef PLAT_PROTO_H_
#define PLAT_PROTO_H_

#include "types.h"
#include "arch/armv7-a/io.h"

#define GPIO14_MASK ~(7 << 12)
#define GPIO15_MASK ~(7 << 15)
#define ALT5_MASK    (2)
#define GPIO14_SHIFT (12)
#define GPIO15_SHIFT (15)

#define GPFSEL1   0xFE200004
#define GPSET0    0xFE20001C
#define GPCLR0    0xFE200028
#define GPPUD     0xFE2000E4
#define GPPUDCLK0 0xFE200098

#define IRQ_PENDING_0       (0xFE00B200)
#define ENABLE_IRQS_0       ((u32 *)0xFE00B210)
#define ENABLE_IRQS(n)      ((ENABLE_IRQS_0 + ((n/32) * 4)))

#define SYSTEM_TIMER_IRQ_0  (1 << 0)
#define SYSTEM_TIMER_IRQ_1  (1 << 1)
#define SYSTEM_TIMER_IRQ_2  (1 << 2)
#define SYSTEM_TIMER_IRQ_3  (1 << 3)


#define AUX_MU_BAUD(baud) ((AUX_UART_CLOCK/(baud*8))-1)
#define AUX_UART_CLOCK 500000000

extern void plat_muart_init();
extern void plat_uart_send(unsigned int c);
extern void plat_irq_unmask(u32 irq);

extern void enable_irq();
extern void irq_handle(unsigned int irq);

extern void dummy();

#endif   /* PLAT_PROTO_H_ */
