#ifndef _AM335X_INTR_H
#define _AM335X_INTR_H

#define INTC_REGS 0x48200000  // BBB ARM Interrupt Controller base address
#define INTC_SYSCONFIG  INTC_REGS + 0x10
#define INTC_SYSSTATUS  INTC_REGS + 0x14
#define INTC_SIR_IRQ    INTC_REGS + 0x40
#define INTC_CONTROL    INTC_REGS + 0x48
#define INTC_MIR_CLEAR0 INTC_REGS + 0x88
#define INTC_MIR_CLEAR2 INTC_REGS + 0xc8

#define INTC_MIR_CLEAR_BANK(n) \
	(INTC_MIR_CLEAR0 + ( 0x20 * (n >> 5)))

#define INTC_IRQ_N_MASK 0x7f

#endif   /* _AM335X_INTR_H */
