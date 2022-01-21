/* k_main.c */

void k_main(void) {

	/* print splash screen */
	const short f_color = 0x0F00;
	const char* splash = "Hello cpp world!";
	short* vga = (short*)0xb8000;
	
	for (int i = 0; i<16;++i) {
        	vga[i+80] = color | hello[i];
	}
}
