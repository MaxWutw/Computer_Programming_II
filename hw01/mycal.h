#ifndef _MYCAL_H_
#define _MYCAL_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
int32_t calculate(char *pEpr, int32_t base, char **ppResult);
int32_t convert2base10(char *data, int8_t *wrong);
int8_t valid(const char* str);

#endif