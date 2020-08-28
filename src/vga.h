#ifndef VGA_H
#define VGA_H

#include "system.h"

#define WIDTH 80
#define HEIGHT 25
#define VGA_ADDRESS 0xB8000

int vga_indx, vga_line;
char vga_colour;
short *vga_ptr;

void vga_init(char fg, char bg);
short vga_gen_char(char ch);
void vga_handle_overflow();
void vga_putch(char ch);
void dab_on_haters(char ch);
void vga_puts(char *str);
void vga_cls();
void vga_newline();
void vga_move_cursor();

enum vga_colours {
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHTGREY,
	DARKGREY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTCYAN,
	LIGHTRED,
	LIGHTMAGENTA,
	LIGHTBROWN,
	WHITE
};

#endif 
