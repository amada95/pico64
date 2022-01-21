/* d_vga.c */

#include "d_vga.h"

unsigned short *g_vga_buffer;

static unsigned short vga_entry(unsigned char ch, unsigned char f_color, unsigned char b_color) {
	unsigned short ax = 0;
	unsigned char ah, al = 0;

	ah = b_color;
	ah <<= 4;
	ah |= f_color;
	ax = ah;
	ax <<= 8;
	al = ch;
	ax |= al;

	return ax;
}

static void vga_buffer_clear(unsigned short **vga_buffer, unsigned char f_color, unsigned char b_color) {
	unsigned int i;
	for (i = 0; i < VGA_BUFSIZE; ++i) {
		*(vga_buffer)[i] = vga_entry('\0', f_color, b_color);
	}
	return;
}

void vga_init(unsigned char f_color, unsigned char b_color) {
	g_vga_buffer = (unsigned short*) VGA_ADDRESS;
	vga_buffer_clear(&g_vga_buffer, f_color, b_color);
	return;
}
