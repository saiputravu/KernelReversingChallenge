#include "system.h"

void memcpy(char *dest, char *src, int count) {
	for (int i = 0; i < count; ++i)
		dest[i] = src[i];
}


void memset(char *dest, char val, int count) {
	for (int i = 0; i < count; ++i)
		dest[i] = val;
}


void memsetw(short *dest, short val, int count) {
	for (int i = 0; i < count; ++i)
		dest[i] = val;
}

int strlen(char *str) {
	int i = 0;
	while (*(str + i))
		++i;
	return i;
}

int strcmp(char *str1, char *str2, int n) {
	for (int i = 0; i < n; ++i) {
		if (str1[i] != str2[i])
			return 0;
	}	
	return 1;
}

void write_port (short port, char data){
	asm volatile("outb %0, %1" : : "dN"(port), "a"(data) );
}

char read_port (short port) {
	char recv;	
	asm volatile("inb %0, %1" : "=a" (recv) : "dN" (port));
	return recv;
}

