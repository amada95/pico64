/* d_keyboard.c */

/* function prototypes */
static unsigned char byte_in(unsigned short port);
static void byte_out(unsigned short port, unsigned char data);

char keyboard_get_input(void);
void keyboard_wait(unsigned int timer_count);


/* functions */

static unsigned char byte_in(unsigned short port) {
	unsigned int data;
	asm volatile("inb %1, %0" : "=a"(ret) : "d"(port));
	return data;
}

static void byte_out(unsigned short port, unsigned char data) {
        asm volatile("outb %1, %0" : "=a"(data) : "d"(port));
        return;
}

char keyboard_get_input(void) {
	char ch = 0;
	while ((ch = byte_in(KEYBOARD_PORT) != 0) {
		if (ch > 0) {
			return ch;
		}
	}
	return ch;
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
