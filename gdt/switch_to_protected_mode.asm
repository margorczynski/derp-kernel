;
;	Loads the GDT from the 'gdt.asm' module and enters protected mode
;	NOTE: There NEEDS to be a 'begin_protected_mode' label for it to jump after initialization
;

[bits 16]

switch_to_protected_mode:			; switch to the protected mode of the CPU

	cli					; turn off real mode interrupt handling as it
						; is not valid any longer for protected mode until
						; a proper interrupt vector is set
	
	lgdt [gdt_descriptor]			; load the GDT which defines the segments

	mov eax, cr0				; set the first bit of CR0 (a control register)
	or eax, 0x1				; set the first bit of eax to 1
	mov cr0, eax				; load the value stored in EAX to the CR0 register

	jmp CODE_SEG_OFFSET:init_protected_mode	; make a 'far jump' (to a new segment) to the 32-bit code
						; this also forces the CPU to flush the cache of pre-fetched
						; instructions (which can be 16-bit real mode instructions)

%include "gdt/gdt.asm" 

[bits 32]

init_protected_mode:		; initialize registers and the stack after entering the protected mode
	
	mov ax, DATA_SEG_OFFSET	; set all the segment registers to the data segment offset
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ebp, 0x90000	; update the stack position to the top of the free space
	mov esp, ebp

	call begin_protected_mode
