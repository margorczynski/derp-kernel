;
;	Basic bootloader for the derp-kernel (TM)
;

[org 0x7c00]

	mov bp, 0x9000	; set the stack pointer to free space
	mov sp, bp

	mov bx, BOOT_MSG		; print message that we're in real mode
	call print_string_real_mode

	call switch_to_protected_mode	; switch to the CPU's protected mode

;	jmp $

; Message variables
BOOT_MSG 		db "Started boot process (currently in real-mode)", 0
PROTECTED_MODE_MSG	db "Successfuly entered the CPU's 32-bit real mode", 0	

; Includes
%include "print_string/print_string_real_mode.asm"
%include "print_string/print_string_protected_mode.asm"
%include "gdt/switch_to_protected_mode.asm"

[bits 32]

begin_protected_mode:
	
	mov ebx, PROTECTED_MODE_MSG 
	call print_string_protected_mode

	jmp $

; Bootsector padding (needs to be 512-byte long)
times 510-($-$$) db 0
dw 0xaa55

