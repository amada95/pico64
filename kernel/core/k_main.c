/* k_main.c */

#include "../drivers/vga/d_vga.h" //TODO: remove relative path in include

void k_main(void) {

	/* print splash screen */
	vga_init(YELLOW, BLACK);
	vga_print_string("beeOS", YELLOW, BLACK);
	vga_print_newline(YELLOW, BLACK);
}
