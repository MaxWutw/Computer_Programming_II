#ifndef _MYSTRING_H_
#define _MYSTRING_H_
#include <stdio.h>
#include <stdint.h>

char *mystrchr(const char *s, int c);
char *mystrrchr(const char *s, int c);
size_t mystrspn(const char *s, const char *accept); 
size_t mystrcspn(const char *s, const char *reject); 
char *mystrpbrk(const char *s, const char *accept);
char *mystrstr(const char *haystack, const char *needle); 
char *mystrtok(char *str, const char *delim);

#endif