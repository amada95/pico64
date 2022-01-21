/* vga.h */

#pragma once

#define VGA_ADDRESS 0xB8000
#define VGA_BUFSIZE 2200

/* function prototypes go here */

void vga_init(unsigned char f_color, unsigned char b_color);

/* *** */

enum vga_color {
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	GREY,
	DARK_GREY,
	BRIGHT_BLUE,
	BRIGHT_GREEN,
	BRIGHT_CYAN,
	BRIGHT_RED,
	BRIGHT_MAGENTA,
	YELLOW,
	WHITE,
};
