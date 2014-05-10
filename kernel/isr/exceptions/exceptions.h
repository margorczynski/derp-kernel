#ifndef __KERNEL_ISR_EXCEPTIONS_H__
#define __KERNEL_ISR_EXCEPTIONS_H__

#include <stdint.h>

void isr_exception_division_by_zero(void);
void isr_exception_debug(void);
void isr_exception_non_maskable_interrupt(void);
void isr_exception_breakpoint(void);
void isr_exception_overflow(void);
void isr_exception_bound_range_exceeded(void);
void isr_exception_invalid_opcode(void);
void isr_exception_device_not_available(void);
void isr_exception_double_fault(uint32_t exception_error_code);
void isr_exception_coprocessor_segment_overrun(void);
void isr_exception_invalid_tss(uint32_t exception_error_code);
void isr_exception_segment_not_present(uint32_t exception_error_code);
void isr_exception_stack_segment_fault(uint32_t exception_error_code);
void isr_exception_general_protection_fault(uint32_t exception_error_code);
void isr_exception_page_fault(uint32_t exception_error_code);
void isr_exception_x87_floating_point(void);
void isr_exception_aligment_check(void);
void isr_exception_machine_check(void);
void isr_exception_simd_floating_point(void);
void isr_exception_virtualization_exception(void);
void isr_exception_security_exception(void);

#endif
