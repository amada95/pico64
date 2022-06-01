#include "drivers/vga/vga.h"
#include "drivers/keyboard/keyboard.h"
#include "drivers/keyboard/keymap.h"

void k_main(void) {

	/***** BEGIN TESTING CODE *****/

	/* print splash screen */
	vga_init(BRIGHT_CYAN, BLACK);
	vga_print_string("pico64 v0.0.0", BRIGHT_CYAN, BLACK);
	vga_print_newline(BRIGHT_CYAN, BLACK);
	for (unsigned char i = 0; i < 80; i++) vga_print_char(220, BRIGHT_CYAN, BLACK);
	vga_print_newline(BRIGHT_CYAN, BLACK);
	vga_print_newline(BRIGHT_CYAN, BLACK);
	vga_print_string("> ", BRIGHT_CYAN, BLACK);

	/* test keyboard input */
	char keycode = 0;
	char ch = 0;
	do {
		keycode = keyboard_get_keycode();
		if(keycode == KEY_ENTER) {
			vga_print_newline(BRIGHT_CYAN, BLACK);
		} else {
			ch = keymap_query(keycode);
			if (ch != 0) {
				vga_print_char(ch, BRIGHT_CYAN, BLACK);
			}
		}
		keyboard_wait(0x095FFFFF);
	} while (1);

	/***** END TESTING CODE *****/

}
