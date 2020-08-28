#include "idt.h"

char keyboard_map[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

void idt_set_gate(char indx, long base, short selector, char flags) {
	
	// Set base
	idt[indx].base_low = base & 0xffff;
	idt[indx].base_high = (base & 0xffff0000) >> 16;
	
	// Set selector
	idt[indx].selector = selector;
	
	// Set flags
	idt[indx].flags = flags;
}

void kb_init(void)
{
	/* 0xFD is 11111101 - enables only IRQ1 (keyboard)*/
	write_port(0x21 , 0xFD);
}

void idt_init() {
	long keyboard_address = (long)keyboard_handler;
	long idt_address;
	long idt_p[2]; 
	
	idt_set_gate(0x21, keyboard_address, 0x08, 0x8e);
	write_port(0x20 , 0x11);
	write_port(0xA0 , 0x11);
	write_port(0x21 , 0x20);
	write_port(0xA1 , 0x28);
	write_port(0x21 , 0x00);  
	write_port(0xA1 , 0x00);  
	write_port(0x21 , 0x01);
	write_port(0xA1 , 0x01);
	write_port(0x21 , 0xff);
	write_port(0xA1 , 0xff);
	
	idt_address = (long)idt;
	idt_p[0] =  (sizeof (struct idt_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
	idt_p[1] = idt_address >> 16;
	load_idt(idt_p);
}

void keyboard_handler_main(void) {
	unsigned char status;
	char keycode;

	/* write EOI */
	write_port(0x20, 0x20);

	status = read_port(0x64);
	/* Lowest bit of status will be set if buffer is not empty */
	if (status & 0x01) {
		keycode = read_port(0x60);
		if(keycode < 0)
			return;
		// HINT 
		/*if(keyboard_map[keycode] == '\n'){
			vga_puts(&keyhist);
		}*/
		vga_putch(keyboard_map[keycode]);
		keyboard_hist(keyboard_map[keycode]);
	}
}

