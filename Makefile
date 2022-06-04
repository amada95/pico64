TARGET	= os.bin

AS	= nasm
SRC_AS	= $(shell find src/ -type f -name "*.asm")
AFLAGS	= -f elf32
OBJS	= $(patsubst %.asm, %.o, $(SRC_AS))

CC	= gcc
SRC_C	= $(shell find src/ -type f -name "*.c")
CFLAGS	= -O2 -std=c99 -nostdlib -ffreestanding -mno-red-zone -fno-exceptions -fno-pie -nostdlib -Wall -Wextra -Werror
SRC_LD	= src/linker.ld
LDFLAGS	= -m32 -T $(SRC_LD)

EMU	= qemu-system-x86_64
EFLAGS	= -hda

.PHONY: all build clean

all:
	@make build
	@echo emulating target...
	@$(EMU) $(EFLAGS) $(TARGET)

build: $(TARGET)
	@echo build successful!

# .c -> .o  +  .o -> .bin
$(TARGET): $(OBJS)
	@$(CC) -o $(TARGET) $(SRC_C) $(OBJS) $(CFLAGS) $(LDFLAGS)

# .asm -> .o
$(OBJS): $(SRC_AS)
	@$(AS) -o $@ $(SRC_AS) $(AFLAGS)

clean:
	rm -rf $(TARGET) $(OBJS)
