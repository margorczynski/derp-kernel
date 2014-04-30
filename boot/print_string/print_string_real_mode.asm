;
;	Print the string stored under the adress held in the BX register (in real 16-bit CPU mode)
;
print_string_real_mode:
	pusha				; push all current register values to the stack
	mov ah, 0x0e		; load into the AH register (upper AX) that we want the BIOS tele-type mode

    mov al, 0x0d        ; print a carriage return char
    int 0x10
    mov al, 0x0a        ; print a line feed char, this will make the string to print in a new line
    int 0x10

print_string_real_mode_loop:
	mov al, [bx]			; load into AL the ASCII code of the char under the adress BX
	
	cmp al, 0			; if the char is NULL then jump to the
	je print_string_real_mode_done	; return label

	int 0x10			; call the needed BIOS routine

	add bx, 1			; increment BX to the address of the next char

	jmp print_string_real_mode_loop	; print next character

print_string_real_mode_done:
	popa				; pop all register values from the stack
	ret				; return to the adress from which it was called
