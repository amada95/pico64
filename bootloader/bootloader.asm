; bootloader.asm ;

section .boot
bits 16					; set assembler output to 16-bits (to run in real mode)
global boot
boot:
	mov ax, 0x2401
	int 0x15			; interrupt and enable A20 bit (to enable accessing more than 1MB of memory)

	mov ax, 0x3
	int 0x10			; interrupt and set vga text mode to 3

	mov [disk], dl			; move dl (BIOS populates with disk number) into disk index

	mov ah, 0x2			; read sectors
	mov al, 6			; sectors to read
	mov ch, 0			; cylinder index
	mov dh, 0			; head index
	mov cl, 2			; sector index
	mov dl, [disk]			; disk index
	mov bx, copy_target		; copy target pointer
	int 0x13			; 0x13 = Disk Services interrupt
	cli				; clear interrupts

	lgdt [gdt_pointer]		; load global descriptor table (gdt)
	mov eax, cr0
	or eax, 0x1			; set protected mode (32-bit mode) bit on special register cr0
	mov cr0, eax

	mov ax, DATA_SEGMENT            ; set ax, ds, es, fs, gs, ss registers to DATA_SEGMENT pointer
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax
        mov ss, ax

	jmp CODE_SEGMENT:bootloader	; long jump to the bootloader code segment

gdt_start:
	dq 0x0
gdt_code:
	dw 0xffff
	dw 0x0
	db 0x0
	db 10011010b
	db 11001111b
	db 0x0
gdt_data:
	dw 0xffff
	dw 0x0
	db 0x0
	db 10010010b
	db 11001111b
	db 0x0
gdt_end:
gdt_pointer:
	dw gdt_end - gdt_start		; gdt size
	dd gdt_start			; pointer to gdt structure
disk:
	db 0X0				; disk index
CODE_SEGMENT equ gdt_code - gdt_start	; pointer to gdt code segment
DATA_SEGMENT equ gdt_data - gdt_start	; pointer to gdt data segment

times 510 - ($-$$) db 0			; pad remaining 510 bytes of first sector with zeroes
dw 0xaa55				; append bootable signature

copy_target:
bits 32					; set assembler output to 32-bits (to run in protected mode)

bootloader:
	mov esp, kernel_stack_top	; move stack pointer to top of the kernel stack
	extern k_main			; define kernel entry point
	call k_main			; call kernel entry point (pauses bootloader execution until kernel stops running)
	jmp halt	
halt:
	cli				; clear interrupts
	hlt				; halt execution

section .bss
align 4
kernel_stack_bottom: equ $
	resb 16384			; reserve 16KB for kernel stack
kernel_stack_top:
