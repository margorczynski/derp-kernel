#ifndef __KERNEL_IDT_H__
#define __KERNEL_IDT_H__

#include <stdint.h>

/*
 * Enum type with the descriptor privilage levels used for creating ISR's with execution protection
 */
typedef enum
{
    RING_0 = 0,
    RING_1,
    RING_2,
    RING_3
} idt_dpl_enum_t;

/*
 * Enum type with the CPU exceptions and their index in the GDT
 */
typedef enum
{
    EXCEPTION_DIVISION_BY_ZERO            = 0,
    EXCEPTION_DEBUG                       = 1,
    EXCEPTION_NON_MASKABLE_INTERRUPT      = 2,
    EXCEPTION_BREAKPOINT                  = 3,
    EXCEPTION_OVERFLOW                    = 4,
    EXCEPTION_BOUND_RANGE_EXCEEDED        = 5,
    EXCEPTION_INVALID_OPCODE              = 6,
    EXCEPTION_DEVICE_NOT_AVAILABLE        = 7,
    EXCEPTION_DOUBLE_FAULT                = 8,
    EXCEPTION_COPROCESSOR_SEGMENT_OVERRUN = 9,
    EXCEPTION_INVALID_TSS                 = 10,
    EXCEPTION_SEGMENT_NOT_PRESENT         = 11,
    EXCEPTION_STACK_SEGMENT_FAULT         = 12,
    EXCEPTION_GENERAL_PROTECTION_FAULT    = 13,
    EXCEPTION_PAGE_FAULT                  = 14,
    //15 - Reserved
    EXCEPTION_X87_FLOATING_POINT          = 16,
    EXCEPTION_ALIGMENT_CHECK              = 17,
    EXCEPTION_MACHINE_CHECK               = 18,
    EXCEPTION_SIMD_FLOATING_POINT         = 19,
    EXCEPTION_VIRTUALIZATION_EXCEPTION    = 20,
    //21-29 - Reserved
    EXCEPTION_SECURITY_EXCEPTION          = 30
    //31 - Reserved
} cpu_exception_enum_t;

/*
 * Enum type with the hardware interrupts and their index in the GDT (mapped by the PIC)
 */
typedef enum
{
    INTERRUPT_KEYBOARD = 0
} hardware_interrupt_enum_t;

/*
 * IDT creation and loading functions
 */
void idt_load_interrupt_descriptor_table(void);

/*
 * ISR creation functions
 */
void idt_create_exception_isr(cpu_exception_enum_t      exception_index, uint32_t isr_address);
void idt_create_interrupt_isr(hardware_interrupt_enum_t interrupt_index, uint32_t isr_address, idt_dpl_enum_t minimum_descriptor_privilage_level);

#endif
