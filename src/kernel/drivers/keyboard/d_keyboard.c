/* d_keyboard.c */

#include "d_keyboard.h"

static unsigned char byte_in(unsigned short port);
char keyboard_get_keycode(void);
void keyboard_wait(unsigned int timer_count);


static unsigned char byte_in(unsigned short port) {
	unsigned char data;
	asm volatile("inb %1, %0" : "=a"(data) : "d"(port));
	return data;
}

char keyboard_get_keycode(void) {
	char keycode = 0;
	while ((keycode = byte_in(KEYBOARD_PORT)) != 0) {
		if (keycode > 0) {
			return keycode;
		}
	}
	return keycode;
}

void keyboard_wait(unsigned int timer_count) {
	while (1) {
		asm volatile("nop");
		timer_count--;
		if(timer_count <= 0) {
			break;
		}
	}
	return;
}
