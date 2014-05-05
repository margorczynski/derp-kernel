; Make the label symbol visible for the linker
[global idt_asm_load_interrupt_descriptor_table_descriptor]

; Declare usage of the external symbol with the IDT descriptor address 
; It is declared in the 'idt.c' source
[extern idt_descriptor_address]

idt_asm_load_interrupt_descriptor_table_descriptor:
    lidt [idt_descriptor_address]
    ret
