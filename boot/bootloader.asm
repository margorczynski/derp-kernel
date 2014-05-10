;
;	Basic bootloader for the derp-kernel (TM)
;

[org 0x7c00]
KERNEL_OFFSET equ 0x1000            ; offset in memory at which the kernel will be loaded into

    mov [BOOT_DRIVE], dl            ; BIOS at boot loads the boot drive number into DL
                                    ; this will remember the value in memory under the address BOOT_DRIVE

	mov bp, 0x9000	                ; set the stack pointer to free space
	mov sp, bp

	mov bx, BOOT_MSG		        ; print message that we're in real mode
	call print_string_real_mode

    call load_kernel                ; load the kernel code from the boot drive into memory

    mov bx, SWITCHING_MODE_MSG      ; print message that we're trying to switch the mode to Protected Mode
    call print_string_real_mode

	call switch_to_protected_mode	; switch to the CPU's protected mode

	jmp $


; Includes
%include "boot/print_string/print_string_real_mode.asm"
%include "boot/print_string/print_string_protected_mode.asm"
%include "boot/gdt/switch_to_protected_mode.asm"
%include "boot/disk_io/disk_read.asm"

[bits 16]

load_kernel:

    mov bx, LOAD_KERNEL_MSG     ; print a message that we're trying to load the kernel
    call print_string_real_mode ;

    mov bx, KERNEL_OFFSET       ; this is the offset at which the kernel will be load into memory
    mov dh, 20                  ; read 15 sectors after the boot sector
    mov dl, [BOOT_DRIVE]        ; from the drive the BIOS started booting
    call disk_read              ; call the function to read it into memory

    ret                         ; return to the call address

[bits 32]

begin_protected_mode:
	
	mov ebx, PROTECTED_MODE_MSG         ; print a message that we're in protected mode of the CPU
	call print_string_protected_mode    ; use the function that writes directly to the video memory

    call KERNEL_OFFSET                  ; jump to the kernel entry point (kernel_main) 

	jmp $

; The number of the boot drive and message variables
BOOT_DRIVE          db 0
BOOT_MSG 		    db "Started boot process (currently in real-mode)", 0
SWITCHING_MODE_MSG  db "Switching to Protected Mode", 0
PROTECTED_MODE_MSG	db "Successfuly entered the CPU's 32-bit real mode", 0	
LOAD_KERNEL_MSG     db "Loading the kernel into memory...", 0

; Bootsector padding (needs to be 512-byte long)
times 510-($-$$) db 0
dw 0xaa55

; Disk space
;times 0x00800000 - ($ - $$) db 0
