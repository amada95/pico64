/* d_vga.c */

#include "d_vga.h"

/* global variables */
unsigned short *g_vga_buffer;
static unsigned int g_vga_index;
static unsigned int g_vga_row;

/* function prototypes */
static unsigned short vga_entry(unsigned char ch, unsigned char f_color, unsigned char b_color);
static void vga_buffer_clear(unsigned short **vga_buffer, unsigned char f_color, unsigned char b_color);

void vga_init(unsigned char f_color, unsigned char b_color);
void vga_print_newline(unsigned char f_color, unsigned char b_color);
void vga_print_char(char ch, unsigned char f_color, unsigned char b_color);
void vga_print_string(char *str, unsigned char f_color, unsigned char b_color);


/* functions */

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
	for (i = 0; i < VGA_BUFSIZE; i++) {
		*(vga_buffer)[i] = vga_entry('\0', f_color, b_color);
	}
	g_vga_row = 1;
	g_vga_index = 0;
	return;
}

void vga_init(unsigned char f_color, unsigned char b_color) {
	g_vga_buffer = (unsigned short*) VGA_ADDRESS;
	vga_buffer_clear(&g_vga_buffer, f_color, b_color);
	return;
}

void vga_print_newline(unsigned char f_color, unsigned char b_color) {
	if (g_vga_row >= 55) {
		vga_buffer_clear(&g_vga_buffer, f_color, b_color);
		g_vga_row = 0;
	}
	g_vga_index = g_vga_row * 80;
	g_vga_row++;
	return;
}

void vga_print_char(char ch, unsigned char f_color, unsigned char b_color) {
	g_vga_buffer[g_vga_index] = vga_entry(ch, f_color, b_color);
	g_vga_index++;
	return;
}

void vga_print_string(char *str, unsigned char f_color, unsigned char b_color) {
	unsigned int i = 0;
	while (str[i]) {
		vga_print_char(str[i], f_color, b_color);
		i++;
	}
	return;
}
