; Make the label symbol visible for the linker
[global gdt_asm_load_global_descriptor_table]

; The structure with the address and size of the GDT
gdtr:
    dw 0
    dd 0

gdt_asm_load_global_descriptor_table:
    cli

    mov eax, [esp+4]
    mov [gdtr+2], eax
    mov ax, [esp+8]
    mov [gdtr], ax

    lgdt [gdtr]

    jmp 0x08:loaded

loaded:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret
