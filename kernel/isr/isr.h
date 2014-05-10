#ifndef __KERNEL_ISR_H__
#define __KERNEL_ISR_H__

/*
 * Creation of ISR's for CPU exceptions and hardware interrupts
 */
void isr_create_exception_isrs(void);
void isr_create_interrupt_isrs(void);

#endif
