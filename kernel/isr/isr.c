#include "isr.h"
#include "exceptions/exceptions.h"
#include "interrupts/interrupts.h"
#include "../idt/idt.h"

/*
 * Create ISR's for all the available CPU exceptions
 * The header and source with all the exception functions is in the 'exceptions/' directory
 */
void isr_create_exception_isrs(void)
{
    idt_create_exception_isr(EXCEPTION_DIVISION_BY_ZERO, (uint32_t) isr_exception_division_by_zero);
    idt_create_exception_isr(EXCEPTION_DEBUG, (uint32_t) isr_exception_debug);
    idt_create_exception_isr(EXCEPTION_NON_MASKABLE_INTERRUPT, (uint32_t) isr_exception_non_maskable_interrupt);
    idt_create_exception_isr(EXCEPTION_BREAKPOINT, (uint32_t) isr_exception_breakpoint);
    idt_create_exception_isr(EXCEPTION_OVERFLOW, (uint32_t) isr_exception_overflow);
    idt_create_exception_isr(EXCEPTION_BOUND_RANGE_EXCEEDED, (uint32_t) isr_exception_bound_range_exceeded);
    idt_create_exception_isr(EXCEPTION_INVALID_OPCODE, (uint32_t) isr_exception_invalid_opcode);
    idt_create_exception_isr(EXCEPTION_DEVICE_NOT_AVAILABLE, (uint32_t) isr_exception_device_not_available);
    idt_create_exception_isr(EXCEPTION_DOUBLE_FAULT, (uint32_t) isr_exception_double_fault);
    idt_create_exception_isr(EXCEPTION_COPROCESSOR_SEGMENT_OVERRUN, (uint32_t) isr_exception_coprocessor_segment_overrun);
    idt_create_exception_isr(EXCEPTION_INVALID_TSS, (uint32_t) isr_exception_invalid_tss);
    idt_create_exception_isr(EXCEPTION_SEGMENT_NOT_PRESENT, (uint32_t) isr_exception_segment_not_present);
    idt_create_exception_isr(EXCEPTION_STACK_SEGMENT_FAULT, (uint32_t) isr_exception_stack_segment_fault);
    idt_create_exception_isr(EXCEPTION_GENERAL_PROTECTION_FAULT, (uint32_t) isr_exception_general_protection_fault);
    idt_create_exception_isr(EXCEPTION_PAGE_FAULT, (uint32_t) isr_exception_page_fault);
    idt_create_exception_isr(EXCEPTION_X87_FLOATING_POINT, (uint32_t) isr_exception_x87_floating_point);
    idt_create_exception_isr(EXCEPTION_ALIGMENT_CHECK, (uint32_t) isr_exception_aligment_check);
    idt_create_exception_isr(EXCEPTION_MACHINE_CHECK, (uint32_t) isr_exception_machine_check);
    idt_create_exception_isr(EXCEPTION_SIMD_FLOATING_POINT, (uint32_t) isr_exception_simd_floating_point);
    idt_create_exception_isr(EXCEPTION_VIRTUALIZATION_EXCEPTION, (uint32_t) isr_exception_virtualization_exception);
    idt_create_exception_isr(EXCEPTION_SECURITY_EXCEPTION, (uint32_t) isr_exception_security_exception);
}

/*
 * Create ISR's for all the available hardware IRQs
 * The header and source with all the interrupt functions is in the 'interrupts/' directory
 */
void isr_create_interrupt_isrs(void)
{
    idt_create_interrupt_isr(INTERRUPT_PROGRAMMABLE_INTERRUPT_TIMER_INTERRUPT, (uint32_t) isr_interrupt_programmable_interrupt_timer_interrupt, RING_0);
    idt_create_interrupt_isr(INTERRUPT_KEYBOARD_INTERRUPT, (uint32_t) isr_interrupt_keyboard_interrupt, RING_0);
    idt_create_interrupt_isr(INTERRUPT_CASCADE, (uint32_t) isr_interrupt_cascade, RING_0);
    idt_create_interrupt_isr(INTERRUPT_COM_2, (uint32_t) isr_interrupt_com_2, RING_0);
    idt_create_interrupt_isr(INTERRUPT_COM_1, (uint32_t) isr_interrupt_com_1, RING_0);
    idt_create_interrupt_isr(INTERRUPT_LPT_2, (uint32_t) isr_interrupt_lpt_2, RING_0);
    idt_create_interrupt_isr(INTERRUPT_FLOPPY_DISK, (uint32_t) isr_interrupt_floppy_disk, RING_0);
    idt_create_interrupt_isr(INTERRUPT_LPT_1, (uint32_t) isr_interrupt_lpt_1, RING_0);
    idt_create_interrupt_isr(INTERRUPT_CMOS_REAL_TIME_CLOCK, (uint32_t) isr_interrupt_cmos_real_time_clock, RING_0);
    idt_create_interrupt_isr(INTERRUPT_FREE_1, (uint32_t) isr_interrupt_free_1, RING_0);
    idt_create_interrupt_isr(INTERRUPT_FREE_2, (uint32_t) isr_interrupt_free_2, RING_0);
    idt_create_interrupt_isr(INTERRUPT_FREE_3, (uint32_t) isr_interrupt_free_3, RING_0);
    idt_create_interrupt_isr(INTERRUPT_PS_2_MOUSE, (uint32_t) isr_interrupt_ps_2_mouse, RING_0);
    idt_create_interrupt_isr(INTERRUPT_FPU_COPROCESSOR, (uint32_t) isr_interrupt_fpu_coprocessor, RING_0);
    idt_create_interrupt_isr(INTERRUPT_PRIMARY_ATA_HARD_DISK, (uint32_t) isr_interrupt_primary_ata_hard_disk, RING_0);
    idt_create_interrupt_isr(INTERRUPT_SECONDARY_ATA_HARD_DISK, (uint32_t) isr_interrupt_secondary_ata_hard_disk, RING_0);
}
