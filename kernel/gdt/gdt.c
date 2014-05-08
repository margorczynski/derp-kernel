#include "gdt.h"

/*
 * The structure type that represents the GDT's entries (descriptors)
 */
typedef struct __attribute__((packed))
{
    uint16_t limit;
    uint16_t address_lower;
    uint8_t  address_middle;
    uint8_t  access;
    uint8_t  granularity;
    uint8_t  address_higher;
} _gdt_entry_struct_t;

/*
 * The GDT that consists of 4 entries (one NULL needed by the CPU, one code and one data descriptors)
 * As this is a static variable the memory is zero'ed out 
 */
static _gdt_entry_struct_t _global_descriptor_table[3];

/*
 * The external symbol of the label that contains the code that will load the GDT
 * Takes the address and size of the GDT as arguments (in that order)
 */
extern void gdt_asm_load_global_descriptor_table(uint32_t, uint16_t);

/*
 * Load the GDT into the CPU using the 'LGDT' instruction
 */
void gdt_load_global_descriptor_table(void)
{
    gdt_asm_load_global_descriptor_table( (uint32_t) _global_descriptor_table, sizeof(_global_descriptor_table));
}

/*
 * Create a basic flat layout
 */
void gdt_create_flat_layout(void)
{
    //Code segment
    
    _global_descriptor_table[1].limit = 0xffff;

    _global_descriptor_table[1].address_lower  = 0x0;
    _global_descriptor_table[1].address_middle = 0x0;
    _global_descriptor_table[1].address_higher = 0x0;

    _global_descriptor_table[1].access      = 0b10011010;
    _global_descriptor_table[1].granularity = 0b11001111;

    //Data segment
    //
    _global_descriptor_table[2].limit = 0xffff;

    _global_descriptor_table[2].address_lower  = 0x0;
    _global_descriptor_table[2].address_middle = 0x0;
    _global_descriptor_table[2].address_higher = 0x0;

    _global_descriptor_table[2].access      = 0b10010010;
    _global_descriptor_table[2].granularity = 0b11001111;
}
