;
;   This will make the bootloader jump strait to 'kernel_main', the kernels entry point
;
[bits 32]               ; this will be called in 32-bit Protected Mode
[extern kernel_main]    ; make the linker resolve this label/symbol

call kernel_main        ; jump to the kernels entry point
jmp $                   ; hang after return from the kernel code
