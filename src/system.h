#ifndef SYSTEM_H
#define SYSTEM_H

void memcpy(char *dest, char *src, int count);
void memset(char *dest, char val, int count);
void memsetw(short *dest, short val, int count);
int strlen(char *str);
void write_port (short port, char data);
char read_port (short port);
int strcmp(char *str1, char *str2, int n);

#endif
