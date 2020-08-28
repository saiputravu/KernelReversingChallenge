#ifndef IDT_H
#define IDT_H

#include "system.h"
#include "vga.h"
#include "flag.h"

#define IDT_SIZE 256

struct idt_entry {
	short base_low;
	short selector;
	char zero;	// always zero
	char flags;
	short base_high;
} __attribute__ ((packed));
// Prevent compiler optimization 

struct idt_entry idt[IDT_SIZE];

// Defined in the asm 
extern void load_idt();
extern void keyboard_handler();

extern char *keyhist;

void idt_set_gate(char indx, long base, short selector, char flags);
void idt_init();
void keyboard_handler_main();
void kb_init();

#endif

