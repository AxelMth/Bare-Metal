#ifndef IRQ_H
#define IRQ_H

#define enable_irq() asm volatile ("cpsie i")
#define disable_irq() asm volatile ("cpsid i")

void irq_init(void);
void irq_enable(int irq_number);
void irq_disable(int irq_number);

#endif // IRQ_H
