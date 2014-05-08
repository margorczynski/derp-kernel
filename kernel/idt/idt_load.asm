; Make the label symbol visible for the linker
[global idt_asm_load_interrupt_descriptor_table]

; The structure with the address and size of the IDT
idtr:
    dw 0
    dd 0

idt_asm_load_interrupt_descriptor_table:
    mov al, 0xff ; disable the PIC interrupt handling
    out 0xa1, al
    out 0x21, al

    mov eax, [esp+4]  ; load the structure with the passed arguments
    mov [idtr+2], eax
    mov ax, [esp+8]
    mov [idtr], ax

    lidt [idtr] ; load the IDT 

    ret
