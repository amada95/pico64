bits 16					; set assembler output to 16-bits (to run in real mode)
org 0x7c00				; set assembler output to start at the end of the MBR

boot:
	mov ax, 0x2401
	int 0x15			; enable A20 bit (to enable accessing more than 1MB of memory)
	mov ax, 0x3
	int 0x10			; set vga text mode to 3
	lgdt [gdt_pointer]		; load global descriptor table (gdt)
	mov eax, cr0
	or eax, 0x1			; set protected mode (32-bit mode) bit on special register cr0
	mov cr0, eax
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
CODE_SEGMENT equ gdt_code - gdt_start	; pointer to gdt code segment
DATA_SEGMENT equ gdt_data - gdt_start	; pointer to gdt data segment


bits 32					;set assembler output to 32-bits (to run in protected mode)
bootloader:
	mov ax, DATA_SEGMENT		; set ax, ds, es, fs, gs, ss registers to DATA_SEGMENT pointer
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	mov esi, vga_test_hello
	mov ebx, 0xb8000
	jmp .vga_test_loop

.vga_test_loop:
	lodsb
	or al, al
	jz vga_test_halt
	or eax, 0x0100
	mov word [ebx], ax
	add ebx, 2
	jmp .vga_test_loop
vga_test_halt:
	cli
	hlt
vga_test_hello: db "hello, world", 0

times 510 - ($-$$) db 0			; pad remaining 510 bytes with zeroes
dw 0xaa55				; append bootable signature
