#ifndef STRING_H
#define STRING_H

#define EOL '\0'

void int_to_ascii(int n, char str[]);
void reverse(char s[]);
int strlen(char s[]);
void backspace(char s[]);
void append(char s[], char n);
int strcmp(char s1[], char s2[]);
char* to_lower(char* s);

#endif
