[org 0x7c00]

	mov bx, BOOT_MSG
	call print_string_real_mode

	jmp $

; Message variables
BOOT_MSG db "Started boot process (currently in real-mode)", 0

; Includes
%include "../print_string/print_string_real_mode.asm"

; Bootsector padding (needs to be 512-byte long)
times 510-($-$$) db 0
dw 0xaa55

