#ifndef CPU_ARCH_H_
#define CPU_ARCH_H_

void dog_spawn();
void write_vbar();

void enable_irq();
void irq_handle(unsigned int irq);

#endif   /* CPU_ARCH_H_ */
