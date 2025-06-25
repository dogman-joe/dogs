#ifndef CPU_ARCH_H_
#define CPU_ARCH_H_

void dog_spawn(void);
void write_vbar(void);

void arch_handle_irq(void);
void enable_irq(void);
void irq_handle(unsigned int irq);

#endif   /* CPU_ARCH_H_ */
