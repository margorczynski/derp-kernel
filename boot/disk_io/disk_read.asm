;
;   Read DH sectors from the drive (just after the bootsector) DL and store the read data under the adress ES:BX
;

disk_read:

    pusha               ; remember the state of all the registers after the call happens 
    push dx             ; remember the value of DX (more specifically DH) to check for any errors later on

    mov ah, 0x02        ; this will tell the BIOS routine to use the read sector function
    mov al, dh          ; read DH sectors from the disk
    mov ch, 0x00        ; the cyllinder is 0
    mov dh, 0x00        ; the head is 0
    mov cl, 0x10        ; start reading from the second sector - just after the 512-byte bootsector
    jmp $

    int 0x13            ; execute the BIOS interrupt routine to read the disk

    ;jc disk_read_error  ; if the error flag is set by the BIOS 0x13 ISR then jump to the error routine

    pop dx              ; load the original value of DX from the stack
    cmp dh, al          ; compare the number of read and requested sectors
    jne disk_read_error ; if the number of read sectors is not equal the amount we requested jump to the error routine
    
    popa                ; restore the registers after the read is completed
    ret                 ; return to the call address


disk_read_error:

    mov bx, DISK_READ_ERROR_MSG ; load the address of the error message to BX
    call print_string_real_mode ; call the print function, this is included in boot.asm
    jmp $                       ; hang the CPU


; Error message string variable
DISK_READ_ERROR_MSG db "Disk read error, hanging...", 0
