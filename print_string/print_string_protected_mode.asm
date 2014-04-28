;
;	Print the string stored under the adress held in the EBX register (in protected 32-bit CPU mode)
;
[bits 32]

VIDEO_MEMORY equ 0xb8000			; the address of the beginning of the video meory
WHITE_ON_BLACK equ 0x0f				; tell the GPU to render white letters on a black background

print_string_protected_mode:
	pusha					; push all current values held in the registers to the stack
	mov edx, VIDEO_MEMORY			; load into EDX the video memory starting address

print_string_protected_mode_loop:
	mov al, [ebx]				; load into AL the ASCII code of the char stored under the adress pointed by EBX
	mov ah, WHITE_ON_BLACK			; load into AH the 'white on black' code

	cmp al, 0				; if the character is NULL then jump to return label
	je print_string_protected_mode_done

	mov [edx], ax				; save into the video memory the ASCII code of the character we want to print out (stored in AL) and the colors used (stored in AH)

	add ebx, 1				; increment EBX to the adress of the next char we want to print out
	add edx, 2				; increment EDX to the adress of the next video memory cell

	jmp print_string_protected_mode_loop	; print next char

print_string_protected_mode_done:
	popa					; pop all register values from the stack
	ret					; jump to the adress from which the function was called

