#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>


void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
void *memmove(void *dest, const void *src, size_t n);
int   memcmp(const void *s1, const void *s2, size_t n);

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
