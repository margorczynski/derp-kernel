#ifndef __KERNEL_IDT_H__
#define __KERNEL_IDT_H__

#include <stdbool.h>
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
 * IDT creation and loading functions
 */
void idt_load_interrupt_descriptor_table(void);

/*
 * ISR creation functions
 */
void idt_create_interrupt_service_routine(uint8_t irq_number, uint32_t isr_address, idt_dpl_enum_t minimum_descriptor_privilage_level);

#endif
