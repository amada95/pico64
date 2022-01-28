#include "drivers/vga/vga.h"
#include "drivers/keyboard/keyboard.h"
#include "drivers/keyboard/keymap.h"

void k_main(void) {

	/***** BEGIN TESTING CODE *****/

	/* print splash screen */
	vga_init(YELLOW, BLACK);
	vga_print_string("beeOS r0.0.0", YELLOW, BLACK);
	vga_print_newline(YELLOW, BLACK);
	for (unsigned char i = 0; i < 80; i++) vga_print_char(176, YELLOW, BLACK);
	vga_print_newline(YELLOW, BLACK);
	vga_print_newline(YELLOW, BLACK);
	vga_print_string("> ", YELLOW, BLACK);

	/* test keyboard input */
	char keycode = 0;
	char ch = 0;
	do {
		keycode = keyboard_get_keycode();
		if(keycode == KEY_ENTER) {
			vga_print_newline(YELLOW, BLACK);
		} else {
			ch = keymap_query(keycode);
			if (ch != 0) {
				vga_print_char(ch, YELLOW, BLACK);
			}
		}
		keyboard_wait(0x095FFFFF);
	} while (1);

	/***** END TESTING CODE *****/

}
