#include "idt.h"

/*
 * The descriptor structure of the IDT
 */
static struct __attribute__((packed))
{
    uint16_t idt_size;    //the size (int bytes) of the IDT
    uint32_t idt_address; //the address of the IDT's first entry
} _idt_descriptor_struct_s;

/*
 * The structure type that represents the IDT's descriptor entries
 */
typedef struct __attribute__((packed))
{
    uint16_t address_lower;
    uint16_t gdt_selector;
    uint8_t  zero;
    uint8_t  type_attribute;
    uint16_t address_higher;
} _idt_entry_struct_t;

/*
 * The IDT that consists of 256 entries (the number of interrupts handled)
 */
static _idt_entry_struct_t _interrupt_descriptor_table[256];

/*
 * The global symbol with the address of the IDT descriptor
 * This is used by the assembly to load it using the 'LIDT' instruction
 * as it cannot be done in inline assembly
 */
extern uint32_t idt_descriptor_address = (uint32_t) &_idt_descriptor_struct_s;

/*
 * The external symbol of the label that contains the code that will load the IDT
 */
extern void idt_asm_load_interrupt_descriptor_table_descriptor(void);

/*
 * Functions
 */


/*
 * Create the IDT descriptor to be used by the CPU LIDT instruction
 */
void idt_create_interrupt_descriptor_table(void)
{
    _idt_descriptor_struct_s.idt_size    = (sizeof(_idt_entry_struct_t) * 256) - 1;
    _idt_descriptor_struct_s.idt_address = (uint32_t) _interrupt_descriptor_table;
}

/*
 * Load the IDT descriptor into the CPU using the LIDT instruction
 */
void idt_load_interrupt_descriptor_table_descriptor(void)
{
    //We need to load the descriptor of the IDT directly in Assembly
    idt_asm_load_interrupt_descriptor_table_descriptor();
}
