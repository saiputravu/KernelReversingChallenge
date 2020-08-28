[BITS 32]
global start
start:
	mov esp, _sys_stack
	jmp stublet

; Must be 4 byte aligned 
ALIGN 4 

mboot:
	; Flags and magic bytes
	MULTIBOOT_PAGE_ALIGN	equ 1<<0
	MULTIBOOT_MEMORY_INFO	equ 1<<1
	MULTIBOOT_ABOUT_KLUDGE	equ 1<<16
	
	MULTIBOOT_HEADER_MAGIC	equ 0x1BADB002
	MULTIBOOT_HEADER_FLAGS	equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_ABOUT_KLUDGE | MULTIBOOT_MEMORY_INFO
	MULTIBOOT_HEADER_CHECK	equ - (MULTIBOOT_HEADER_FLAGS + MULTIBOOT_HEADER_MAGIC)
	EXTERN code, bss, end

	; File signature
	dd MULTIBOOT_HEADER_MAGIC
	dd MULTIBOOT_HEADER_FLAGS
	dd MULTIBOOT_HEADER_CHECK

	;AOUT kludge - must be a physical addr
	;Linker fills in data about this 
	dd mboot
	dd code
	dd bss
	dd end
	dd start

; Endless loop
stublet:
	extern main
	call main
	jmp $

extern keyboard_handler_main
global keyboard_handler
keyboard_handler:
	call keyboard_handler_main
	iretd

global load_idt
load_idt:
	mov edx, [esp+4]
	lidt [edx]
	sti
	ret	

;Bss
;Stack grows downwards so we declare size first 
SECTION .bss
	resb 8192
_sys_stack:

