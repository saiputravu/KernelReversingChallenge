#include "main.h"

void kernel_init() {
	idt_init();
	kb_init();
	vga_init(LIGHTRED, BLACK);
}

void main(){
	kernel_init();
	vga_puts("Hahaha welcome!\n");
	
	// Ensure the kernel doesn't die
	// Also have an asm loop
	for(;;);
}
