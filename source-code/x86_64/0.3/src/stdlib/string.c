#include "string.h"


/**
 * K&R implementation
 */
void int_to_ascii(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    reverse(str);
}

/* K&R */
void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* K&R */
int strlen(char s[]) {
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

void append(char s[], char n) {
    int len = strlen(s);
    s[len] = n;
    s[len+1] = '\0';
}

void backspace(char s[]) {
    int len = strlen(s);
    s[len-1] = '\0';
}

/* K&R 
 * Returns <0 if s1<s2, 0 if s1==s2, >0 if s1>s2 */
int strcmp(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

char *strcpy(char *dest, const char *src) {
    char *ret = dest;
    while ((*dest++ = *src++) != '\0');
    return ret;
}



void clear_buffer(char *buffer, int size) {
    memset(buffer, '\0', size);  // Set entire buffer to '\0'
}




// Helper function to convert an integer to a string (base-10 for decimal)
void int_to_str(int num, char* buffer) {
    int i = 0, is_negative = 0;

    // Handle 0 explicitly
    if (num == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
        return;
    }

    // Handle negative numbers
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    // Process individual digits
    while (num != 0) {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }

    // Add negative sign if necessary
    if (is_negative) {
        buffer[i++] = '-';
    }

    // Null-terminate the string
    buffer[i] = '\0';

    // Reverse the string
    for (int j = 0; j < i / 2; j++) {
        char temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }
}

// Helper function to convert an integer to a string in any base (binary, hex, etc.)
void int_to_base_str(unsigned int num, char* buffer, int base) {
    int i = 0;
    const char* digits = "0123456789ABCDEF";

    // Handle 0 explicitly
    if (num == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
        return;
    }

    // Process individual digits based on the base
    while (num != 0) {
        buffer[i++] = digits[num % base];
        num /= base;
    }

    // Null-terminate the string
    buffer[i] = '\0';

    // Reverse the string
    for (int j = 0; j < i / 2; j++) {
        char temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }
}




