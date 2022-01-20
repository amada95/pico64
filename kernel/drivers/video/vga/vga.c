// vga.c

/* preprocessor */
#include "vga.h"
#include "types.h"

#define VGA_ADDRESS 0xB8000
#define BUFSIZE 2200


/* function prototypes */
uint16 vga_entry(unsigned char ch, uint8 f_color, uint8 b_color);
void vga_buffer_clear(uint16 **buffer, uint8 f_color, uint8 b_color);
void vga_init(uint8 f_color, uint8 b_color);
void vga_print_newline(uint8 f_color, uint8 b_color);
void vga_print_char(char ch, uint8 f_color, uint8 b_color);
void vga_print_string(char *str, uint8 f_color, uint8 b_color);
void vga_print_int(int num, uint8 f_color, uint8 b_color);

static uint32 util_countdigits(int num);
static void util_itoa(int num, char *str_num);


/* global variables */
uint16 *g_vga_buffer;			// VGA video memory buffer array
uint32 g_vga_index;     		// index for video memory buffer array
static uint32 vga_nextline_index;       // counter index to store new lines


/* functions */

/* vga_entry
*  create vga entry given ASCII char, foreground and background colors.
*/
uint16 vga_entry(unsigned char ch, uint8 f_color, uint8 b_color)
{
/*
*  16-bit vga buffer elements (ax register)
*
*       8-bits higher (ah):
*         lower 4 bits - foreground color
*         higher 4 bits - background color
*       8 bits lower (al):
*         all 8 bits - ASCII char to print
*
*/
	uint16 ax = 0;
	uint8 ah = 0, al = 0;

	ah = b_color;
	ah <<= 4;
	ah |= f_color;
	ax = ah;
	ax <<= 8;
	al = ch;
	ax |= al;

	return ax;
}

/* vga_buffer_clear
*  zero out VGA buffer array
*/
void vga_buffer_clear(uint16 **buffer, uint8 f_color, uint8 b_color)
{
	uint32 i;
	for(i = 0; i < BUFSIZE; i++)
	{
		(*buffer)[i] = vga_entry(0x00, f_color, b_color);
	}
}

/* vga_init
*  initialize VGA buffer
*/
void vga_init(uint8 f_color, uint8 b_color)
{
	g_vga_buffer = (uint16*)VGA_ADDRESS;	// initialize VGA buffer to point to VGA video memory
	vga_buffer_clear(&g_vga_buffer, f_color, b_color);	// clear VGA buffer
	g_vga_index = 0;
	vga_nextline_index = 1;
}

/* vga_print_newline
*  print newline by increasing vga index by row length (80)
*/
void vga_print_newline(uint8 f_color, uint8 b_color)
{
	if(vga_nextline_index >= 55)	// reset line index if screen overflows
	{
		vga_nextline_index = 0;
		vga_buffer_clear(&g_vga_buffer, f_color, b_color);
	}
	
	g_vga_index = 80 * vga_nextline_index;
	vga_nextline_index++;
}

/* vga_print_char
*  print single ASCII character to video buffer
*/
void vga_print_char(char ch, uint8 f_color, uint8 b_color)
{
	g_vga_buffer[g_vga_index] = vga_entry(ch, f_color, b_color);
	g_vga_index++;
}

/* vga_print_string
*  print ASCII string to video buffer character-by-character
*/
void vga_print_string(char *str, uint8 f_color, uint8 b_color)
{
	uint32 i = 0;
	while(str[i])
	{
		vga_print_char(str[i], f_color, b_color);
		i++;
	}
}

/* vga_print_int
*  print integer to video buffer by converting it to a string
*/
void vga_print_int(int num, uint8 f_color, uint8 b_color)
{
	char str_num[util_countdigits(num)+1];
	util_itoa(num, str_num);
	vga_print_string(str_num, f_color, b_color);
}

/* util_countdigits
*  static (local-only) utility function for counting the digits in a number
*/
static uint32 util_countdigits(int num)
{
	uint32 count = 0;
	if(num == 0)
		return 1;
	
	while(num > 0)
	{
		count++;
		num = num / 10;
	}

	return count;
}

/* util_itoa
*  static (local-only) utility function for converting integer to a string
*/
static void util_itoa(int num, char *str_num)
{
	int num_digits = util_countdigits(num);
	int i = num_digits - 1;
	char x;

	if(num == 0 && num_digits == 1)
	{
		str_num[0] = '0';
		str_num[1] = '\0';
	} else {
		while(num != 0)
		{
			x = num % 10;
			str_num[i] = x + '0';
			i--;
			num = num / 10;
		}
	
	str_num[num_digits] = '\0';
	}
}
