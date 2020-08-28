#include "vga.h"

void vga_init(char fg, char bg) {
	vga_colour = (bg << 4) | (fg & 0x0f);
	vga_ptr = (short *)VGA_ADDRESS;
	vga_cls();
}

void vga_cls() {
	vga_indx = 0;
	vga_line = 0;
	memsetw(vga_ptr, vga_gen_char(' '), WIDTH * HEIGHT); 
}

short vga_gen_char(char ch) {
	return (vga_colour << 8) | ch;
}

void vga_newline() {
	vga_line++;	
	vga_indx = 0;
	vga_move_cursor();
}

void vga_putch(char ch) {
	switch (ch) {
	case '\n':
		vga_line++;
		vga_indx = 0;
		break;
	default:
		vga_ptr[vga_line * 80 + vga_indx] = vga_gen_char(ch);
		vga_indx++;
		break;
	}
	vga_line %= HEIGHT;
	vga_indx %= WIDTH;
	vga_move_cursor();
}

void dab_on_haters(char ch) {
	switch (ch) {
	case '\n':
		vga_line++;
		vga_indx = 0;
		break;
	default:
		vga_ptr[vga_line * 80 + vga_indx] = vga_gen_char(ch);
		vga_indx++;
		break;
	}
	vga_line %= HEIGHT;
	vga_indx %= WIDTH;
	vga_move_cursor();
}

void vga_puts(char *str) {
	for (int i = 0; i < strlen(str); ++i)
		vga_putch(str[i]);
}


void vga_move_cursor() {
	int temp_indx = (vga_line * WIDTH) + vga_indx;
	write_port(0x3d4, 14);
	write_port(0x3d5, temp_indx >> 8);	// Colour
	write_port(0x3d4, 15);
	write_port(0x3d5, temp_indx);		// Character 
}

