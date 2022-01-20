/* k_vga.c */


/* constants */
#define VGA_ADDRESS 0xB8000
#define VGA_BUFSIZE 2200

/* globals */
unsigned short *g_vga_buffer;
unsigned int g_vga_index;
static unsigned int g_vga_nextline_index;

/* function prototypes */
static unsigned int countdigits(int num);
static void itoa(int num, char *str_num);
static unsigned short k_vga_entry(unsigned char ch, unsigned char f_color, unsigned char b_color);
static void k_vga_buffer_clear(unsigned short **buffer, unsigned char f_color, unsigned char b_color);

void k_vga_init(unsigned char f_color, unsigned char b_color);
void k_vga_print_newline(unsigned char f_color, unsigned char b_color);
void k_vga_print_char(char ch, unsigned char f_color, unsigned char b_color);
void k_vga_print_string(char *str, unsigned char f_color, unsigned char b_color);
void k_vga_print_int(int num, unsigned char f_color, unsigned char b_color);

/* driver functions */
static unsigned int countdigits(int num) {
        unsigned int count = 0;
        if (num == 0) {
                return 1;
        }
        while (num > 0) {
                count++;
                num = num / 10;
        }
        return count;
}

static void itoa(int num, char *str_num) {
        int num_digits = countdigits(num);
        int i = num_digits - 1;
        char x;

        if (num == 0 && num_digits == 1) {
                str_num[0] = '0';
                str_num[1] = '\0';
        } else {
                while (num != 0) {
                        x = num % 10;
                        str_num[i] = x + '0';
                        i--;
                        num = num / 10;
                }
        str_num[num_digits] = '\0';
        }
}

static unsigned short k_vga_entry(unsigned char ch, unsigned char f_color, unsigned char b_color) {
	unsigned short ax = 0;
	unsigned char ah = 0, al = 0;

	ah = b_color;
	ah <<= 4;
	ah |= f_color;
	ax <<= 8;
	al = ch;
	ax |= al;

	return ax;
}

static void k_vga_buffer_clear(unsigned short **buffer, unsigned char f_color, unsigned char b_color) {
        unsigned int i;
        for (i = 0; i < VGA_BUFSIZE; i++) {
                (*buffer)[i] = k_vga_entry(0x00, f_color, b_color);
        }
}

void k_vga_init(unsigned char f_color, unsigned char b_color) {
	g_vga_buffer = (unsigned short*) VGA_ADDRESS;
	k_vga_buffer_clear(&g_vga_buffer, f_color, b_color);
	g_vga_index = 0;
	g_vga_nextline_index = 1;
}

void k_vga_print_newline(unsigned char f_color, unsigned char b_color) {
	if (g_vga_nextline_index >= 55) {	// reset line index if screen overflows (55 columns)
		g_vga_nextline_index = 0;
		k_vga_buffer_clear(&g_vga_buffer, f_color, b_color);
	}
	g_vga_index = 80 * g_vga_nextline_index;
	g_vga_nextline_index++;
}

void k_vga_print_char(char ch, unsigned char f_color, unsigned char b_color) {
	g_vga_buffer[g_vga_index] = k_vga_entry(ch, f_color, b_color);
	g_vga_index++;	//TODO: implement overflow to next column
}

void k_vga_print_string(char *str, unsigned char f_color, unsigned char b_color) {
	unsigned int i = 0;
	while (str[i]) {
		k_vga_print_char(str[i], f_color, b_color);
		i++;
	}
}

void k_vga_print_int(int num, unsigned char f_color, unsigned char b_color) {
	char str_num[countdigits(num) + 1];
	itoa(num, str_num);
	k_vga_print_string(str_num, f_color, b_color);
}
