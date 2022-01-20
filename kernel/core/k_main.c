/* k_main.c */

#include "../drivers/video/vga/k_vga.h" // TODO: remove relative path reference to headers

void k_main(void) {

	/* print splash screen */
	k_vga_init(YELLOW, BLACK);
	k_vga_print_string("beeOS", YELLOW, BLACK);
	k_vga_print_newline(YELLOW, BLACK);

	return;
}
