#ifndef D_VGA_H
#define D_VGA_H

#define VGA_ADDRESS 0xB8000
#define VGA_BUFSIZE 2200

void vga_init (unsigned char f_color, unsigned char b_color);
void vga_print_newline (unsigned char f_color, unsigned char b_color);
void vga_print_char (char ch, unsigned char f_color, unsigned char b_color);
void vga_print_string (char *str, unsigned char f_color,
                       unsigned char b_color);

enum vga_color
{
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
