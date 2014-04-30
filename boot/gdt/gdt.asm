;
;	Simple GDT used for the switch from real to protected mode
;

gdt_start:

gdt_null:	; mandatory NULL descriptor at the beginning
	dd 0x0		
	dd 0x0	; a total of 8 bytes of zero'ed out memory

gdt_code:		; the code segment descriptor
	dw 0xffff	; Limit (bits 0-15)
	dw 0x0		; Base (bits 0-15)
	db 0x0		; Base (bits 16-23) 
	db 10011010b	; 1st flags, type flags
	db 11001111b	; 2nd flags, Limit (bits 16-19)
	db 0x0		; Base (bits 24-31)

gdt_data:		; the data segment descriptor
	dw 0xffff	; Limit (bits 0-15)
	dw 0x0		; Base (bits 0-15)
	db 0x0		; Base (bits 16-23) 
	db 10010010b	; 1st flags, type flags
	db 11001111b	; 2nd flags, Limit (bits 16-19)
	db 0x0		; Base (bits 24-31)

gdt_end:		; used for calculating the size of the GDT

gdt_descriptor:		; the GDT descriptor
	dw gdt_end - gdt_start - 1	; size of the GDT
	
	dd gdt_start			; the start address of the GDT

; The GDT segments offsets
CODE_SEG_OFFSET equ gdt_code - gdt_start
DATA_SEG_OFFSET equ gdt_data - gdt_start
