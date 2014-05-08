#include "idt.h"

/*
 * The structure type that represents the IDT's entries (descriptors)
 */
typedef struct __attribute__((packed))
{
    uint16_t address_lower;
    uint16_t selector;
    uint8_t  zero;
    uint8_t  type_attribute;
    uint16_t address_higher;
} _idt_entry_struct_t;

/*
 * The IDT that consists of 256 entries (the number of interrupts handled)
 */
static _idt_entry_struct_t _interrupt_descriptor_table[256];

/*
 * The external symbol of the label that contains the code that will load the IDT
 * Takes the address and size of the IDT as arguments (in that order)
 */
extern void idt_asm_load_interrupt_descriptor_table_descriptor(uint32_t, uint16_t);


/*
 * Load the IDT descriptor into the CPU using the LIDT instruction
 */
void idt_load_interrupt_descriptor_table(void)
{
    //We need to load the descriptor of the IDT directly in Assembly
    idt_asm_load_interrupt_descriptor_table(_interrupt_descriptor_table, sizeof(_interrupt_descriptor_table));
}

/*
 * Create an ISR for a specific IRQ number (IDT index)
 */
void idt_create_interrupt_service_routine(uint8_t irq_number, uint32_t isr_address, idt_dpl_enum_t minimum_descriptor_privilage_level)
{
    //Dissect the ISR's address into a combination of a lower and higher address
    const uint16_t ADDRESS_LOWER  = (uint16_t) isr_address;
    const uint16_t ADDRESS_HIGHER = (uint16_t) (isr_address >> 16);

    //This type attribute represents an interrupt ISR with a custom present state and minium DPL required for calling it
    const uint8_t TYPE_ATTRIBUTE = 0x80 | (minimum_descriptor_privilage_level << 6) | (0xe);

    //Check if the arguments are correct, if not then exit the function
    if(irq_number > 255 || isr_address < 0)
    {
        return;
    }

    _interrupt_descriptor_table[irq_number].address_lower  = ADDRESS_LOWER;
    _interrupt_descriptor_table[irq_number].address_higher = ADDRESS_HIGHER;

    _interrupt_descriptor_table[irq_number].zero = 0x0;

    _interrupt_descriptor_table[irq_number].selector = 0x08;

    _interrupt_descriptor_table[irq_number].type_attribute = TYPE_ATTRIBUTE;
}
