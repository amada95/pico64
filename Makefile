# TODO: this is garbage! fix it

CC		= gcc
CC_OUT		= kernel.bin
CC_SOURCE	= bootloader.o kernel/core/k_main.c kernel/drivers/vga/d_vga.c kernel/drivers/keyboard/d_keyboard.c kernel/drivers/keyboard/d_keymap.c #TODO: un-hardcode this
CC_FLAGS	= -m32 -O3 -nostdlib -ffreestanding -mno-red-zone -fno-exceptions -fno-pie -fno-stack-protector -Wall -Wextra -Werror -T bootloader/bootloader.ld

ASM		= nasm
ASM_FLAGS	= -f elf32


all:
	@echo assembling bootloader...
	$(ASM) $(ASM_FLAGS) bootloader/bootloader.asm -o bootloader.o
	@echo "compiling kernel"
	$(CC) -o $(CC_OUT) $(CC_SOURCE) $(CC_FLAGS) #TODO: un-hardcode this
	@echo "build complete"

clean:
	@echo "cleaning..."
	rm -rf *.o *.bin
	@echo "clean complete"
