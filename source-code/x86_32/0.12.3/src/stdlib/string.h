#pragma once

#include "../util/util.h"
#include "../driver/vga.h"



void int_to_ascii(int n, char str[]);
void reverse(char s[]);
int strlen(char s[]);
void append(char s[], char n);
void backspace(char s[]);
int strcmp(char s1[], char s2[]);
char *strcpy(char *dest, const char *src);
void clear_buffer(char *buffer, int size);
void int_to_str(int num, char* buffer);
void int_to_base_str(unsigned int num, char* buffer, int base);
