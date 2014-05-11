#ifndef __KERNEL_ISR_INTERRUPTS_H__
#define __KERNEL_ISR_INTERRUPTS_H__

//Master PIC
void isr_interrupt_programmable_interrupt_timer_interrupt(void);
void isr_interrupt_keyboard_interrupt(void);
void isr_interrupt_cascade(void);
void isr_interrupt_com_2(void);
void isr_interrupt_com_1(void);
void isr_interrupt_lpt_2(void);
void isr_interrupt_floppy_disk(void);
void isr_interrupt_lpt_1(void);
//Slave PIC
void isr_interrupt_cmos_real_time_clock(void);
void isr_interrupt_free_1(void);
void isr_interrupt_free_2(void);
void isr_interrupt_free_3(void);
void isr_interrupt_ps_2_mouse(void);
void isr_interrupt_fpu_coprocessor(void);
void isr_interrupt_primary_ata_hard_disk(void);
void isr_interrupt_secondary_ata_hard_disk(void);

#endif
