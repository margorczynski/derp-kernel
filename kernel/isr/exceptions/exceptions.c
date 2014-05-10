#include <stdint.h>

#include "exceptions.h"
#include "../../../drivers/vga/text_mode.h"

static const attribute_struct_t TEXT_ATTRIBUTE_WHITE_ON_BLACK =
{
    .character_color  = VGA_WHITE,
    .intensity        = 1,
    .background_color = VGA_BLACK,
    .blinking         = 0
};

__attribute__((naked)) void isr_exception_division_by_zero(void)
{
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("CPU Exception: Divison by Zero\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_exception_debug(void)
{
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("CPU Exception: Debug\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_exception_non_maskable_interrupt(void)
{
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("CPU Exception: Non Maskable Interrupt\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_exception_breakpoint(void)
{
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("CPU Exception: Breakpoint\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_exception_overflow(void)
{
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("CPU Exception: Overflow\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_exception_bound_range_exceeded(void)
{
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("CPU Exception: Bound Range Exceeded\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_exception_invalid_opcode(void)
{
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("CPU Exception: Invalid Opcode\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_exception_device_not_available(void)
{
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("CPU Exception: Device Not Available\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_exception_double_fault(uint32_t exception_error_code)
{
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("CPU Exception: Double Fault\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_exception_coprocessor_segment_overrun(void)
{
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("CPU Exception: Coprocessor Segment Ovverun\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    for(;;){}

    asm ("popal");
    asm ("iret");
}
__attribute__((naked)) void isr_exception_invalid_tss(uint32_t exception_error_code)
{
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("CPU Exception: Invalid TSS\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_exception_segment_not_present(uint32_t exception_error_code)
{
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("CPU Exception: Segment Not Present\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_exception_stack_segment_fault(uint32_t exception_error_code)
{
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("CPU Exception: Stack Segment Fault\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_exception_general_protection_fault(uint32_t exception_error_code)
{
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("CPU Exception: General Protection Fault\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_exception_page_fault(uint32_t exception_error_code)
{
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("CPU Exception: Page Fault\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_exception_x87_floating_point(void)
{
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("CPU Exception: X87 Floating Point\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_exception_aligment_check(void)
{
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("CPU Exception: Aligment Check\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_exception_machine_check(void)
{
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("CPU Exception: Machine Check\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_exception_simd_floating_point(void)
{
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("CPU Exception: SIMD Floating Point\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_exception_virtualization_exception(void)
{
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("CPU Exception: Virtualization Exception\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    for(;;){}

    asm ("popal");
    asm ("iret");
}

__attribute__((naked)) void isr_exception_security_exception(void)
{
    asm ("pushal");

    vga_clear_screen();
    vga_print_string("CPU Exception: Security Exception\n", TEXT_ATTRIBUTE_WHITE_ON_BLACK);
    vga_print_string("Halting...", TEXT_ATTRIBUTE_WHITE_ON_BLACK);

    for(;;){}

    asm ("popal");
    asm ("iret");
}
