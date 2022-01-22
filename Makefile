TARGET	= os.bin

AS	= nasm
SRC_AS	= $(shell find src/ -type f -name "*.asm")
AFLAGS	= -f elf32
OBJS	= $(patsubst %.asm, %.o, $(SRC_AS))

CC	= gcc
SRC_C	= $(shell find src/ -type f -name "*.c")
CFLAGS	= -O2 -nostdlib -ffreestanding -mno-red-zone -fno-exceptions -fno-pie -nostdlib -Wall -Wextra -Werror
SRC_LD	= $(shell find src/linker -type f -name "*.ld")
LDFLAGS	= -m32 -T $(SRC_LD)


all: $(TARGET)
	@echo build successful!

# compiles c source into objectfiles and link with other objectfiles
$(TARGET): $(OBJS)
	@$(CC) -o $(TARGET) $(SRC_C) $(OBJS) $(CFLAGS) $(LDFLAGS)

# assembles asm source into objectfiles
$(OBJS): $(SRC_AS)
	@$(AS) -o $@ $(SRC_AS) $(AFLAGS)


clean:
	rm -rf $(TARGET) $(OBJS)
