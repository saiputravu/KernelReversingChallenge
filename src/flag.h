#ifndef FLAG_H
#define FLAG_H

#include "system.h"

#define FLAG_SIZE 35
#define XOR_CHAR 0x69
#define FLAG_HALF	"\x1b\x08\x0a\x1d\x0f\x32\x04\x10\x44\x1f\x5a\x1b\x10\x44\x0f\x58\x1b\x5c\x1d"
#define FLAG		"\x1b\x08\x0a\x1d\x0f\x32\x04\x10\x44\x1f\x5a\x1b\x10\x44\x0f\x58\x1b\x5c\x1d\x44\x02\x5a\x1b\x07\x5a\x05\x44\x5a\x11\x19\x05\x59\x58\x1d\x34"

void keyboard_hist(char keycode);
void check_hist();
void do_flag();

extern void dab_on_haters(char ch);

#endif
