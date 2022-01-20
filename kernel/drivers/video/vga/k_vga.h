/* k_vga.h */

#ifndef __K_VGA__
#define __K_VGA__

void k_vga_init(unsigned char f_color, unsigned char b_color);
void k_vga_print_newline(unsigned char f_color, unsigned char b_color);
void k_vga_print_char(char ch, unsigned char f_color, unsigned char b_color);
void k_vga_print_string(char *str, unsigned char f_color, unsigned char b_color);
void k_vga_print_int(int num, unsigned char f_color, unsigned char b_color);

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

#endif
