#include "interrupts.h"
#include "../../../drivers/vga/text_mode.h"
#include "../../../drivers/port_io/port_io.h"

#define MASTER_PIC_COMMAND_PORT 0x20
#define SLAVE_PIC_COMMAND_PORT  0xA0

static const attribute_struct_t TEXT_ATTRIBUTE_WHITE_ON_BLACK =
{
    .character_color  = VGA_WHITE,
    .intensity        = 1,
    .background_color = VGA_BLACK,
    .blinking         = 0
};

/*
 * Master PIC
 */
__attribute__((naked)) void isr_interrupt_programmable_interrupt_timer_interrupt(void)
{
    __asm__ __volatile__ ("cli");
    asm ("pushal");

    vga_print_char('x', TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    port_io_write_byte(MASTER_PIC_COMMAND_PORT, 0x20);

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_interrupt_keyboard_interrupt(void)
{
    __asm__ __volatile__ ("cli");
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("IRQ 1: Keyboard\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    port_io_write_byte(MASTER_PIC_COMMAND_PORT, 0x20);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_interrupt_cascade(void)
{
    __asm__ __volatile__ ("cli");
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("IRQ 2: Cascade\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    port_io_write_byte(MASTER_PIC_COMMAND_PORT, 0x20);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_interrupt_com_2(void)
{
    __asm__ __volatile__ ("cli");
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("IRQ 3: COM2\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    port_io_write_byte(MASTER_PIC_COMMAND_PORT, 0x20);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_interrupt_com_1(void)
{
    __asm__ __volatile__ ("cli");
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("IRQ 4: COM1\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    port_io_write_byte(MASTER_PIC_COMMAND_PORT, 0x20);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_interrupt_lpt_2(void)
{
    __asm__ __volatile__ ("cli");
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("IRQ 5: LPT2\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    port_io_write_byte(MASTER_PIC_COMMAND_PORT, 0x20);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_interrupt_floppy_disk(void)
{
    __asm__ __volatile__ ("cli");
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("IRQ 6: Floppy Disk\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    port_io_write_byte(MASTER_PIC_COMMAND_PORT, 0x20);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_interrupt_lpt_1(void)
{
    __asm__ __volatile__ ("cli");
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("IRQ 7: LPT1\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    port_io_write_byte(MASTER_PIC_COMMAND_PORT, 0x20);

    for(;;){}

    asm ("popal");
    asm ("iret");
}
/*
 * Slave PIC
 */
__attribute__((naked)) void isr_interrupt_cmos_real_time_clock(void)
{
    __asm__ __volatile__ ("cli");
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("IRQ 8: CMOS Real-Time Clock\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    port_io_write_byte(SLAVE_PIC_COMMAND_PORT, 0x20);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_interrupt_free_1(void)
{
    __asm__ __volatile__ ("cli");
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("IRQ 9: Free 1\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    port_io_write_byte(SLAVE_PIC_COMMAND_PORT, 0x20);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_interrupt_free_2(void)
{
    __asm__ __volatile__ ("cli");
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("IRQ 10: Free 2\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    port_io_write_byte(SLAVE_PIC_COMMAND_PORT, 0x20);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_interrupt_free_3(void)
{
    __asm__ __volatile__ ("cli");
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("IRQ 11: Free 3\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    port_io_write_byte(SLAVE_PIC_COMMAND_PORT, 0x20);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_interrupt_ps_2_mouse(void)
{
    __asm__ __volatile__ ("cli");
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("IRQ 12: PS/2 Mouse\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    port_io_write_byte(SLAVE_PIC_COMMAND_PORT, 0x20);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_interrupt_fpu_coprocessor(void)
{
    __asm__ __volatile__ ("cli");
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("IRQ 13: FPU/Coprocessor\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    port_io_write_byte(SLAVE_PIC_COMMAND_PORT, 0x20);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_interrupt_primary_ata_hard_disk(void)
{
    __asm__ __volatile__ ("cli");
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("IRQ 14: Primary ATA Hard Disk\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    port_io_write_byte(SLAVE_PIC_COMMAND_PORT, 0x20);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_interrupt_secondary_ata_hard_disk(void)
{
    __asm__ __volatile__ ("cli");
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("IRQ 15: Secondary ATA Hard Disk\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    port_io_write_byte(SLAVE_PIC_COMMAND_PORT, 0x20);

    for(;;){}

    asm ("popal");
    asm ("iret");
}
