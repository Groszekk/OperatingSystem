section .boot
[bits 16]
global boot

boot:
    mov ax, 0x2401
    int 0x15      ; enable A20 line

    mov ax, 0x3
    int 0x10

    mov [disk], dl

    mov ah, 0x2          ; read sectors
    mov al, 6            ; sectors to read
    mov ch, 0            ; cylinder idx
    mov cl, 2            ; sector idx
    mov dl, [disk]       ; idx
    mov bx, boot2        ; target pointer
    int 0x13

    cli

    lgdt [GDT_DESCRIPTOR]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    mov ax, DATA_SEGMENT
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp CODE_SEGMENT:boot2 ; jump far to new (32bit protected mode) code segment

GDT:
    dq 0x0
    GDT_CODE:
        dw 0xffff
        dw 0x0
        db 0x0
        db 10011010b
        db 11001111b
        db 0x0
    GDT_DATA:
        dw 0xffff
        dw 0x0
        db 0x0
        db 10010010b
        db 11001111b
        db 0x0
GDT_END:

GDT_DESCRIPTOR:
    dw GDT_END - GDT - 1
    dd GDT

disk: db 0x0

CODE_SEGMENT equ GDT_CODE - GDT
DATA_SEGMENT equ GDT_DATA - GDT

times 510 - ($ - $$) db 0
    db 0x55
    db 0xaa

boot2:
    [bits 32]
    mov esp, kernel_stack_top
    extern kmain
    call kmain
    cli
    hlt

; init stack
section .bss
align 4
kernel_stack_bottom: equ $
    resb 16384 ; 16KB
kernel_stack_top: