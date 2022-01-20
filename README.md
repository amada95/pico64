## beeOS
a simple public domain operating system written to embody simplicity, performance, and ultimate hardware control.

### building
note to self:
`gcc -m32 ../kernel/core/kernel.c bootloader.o -o kernel.bin -nostdlib -ffreestanding -mno-red-zone -fno-exceptions -fno-pie -nostdlib -Wall -Wextra -Werror -T bootloader.ld`

`this repository and its README.md are a work in progress`
