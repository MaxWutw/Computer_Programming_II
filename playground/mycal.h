#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int32_t calculate( char *pExpr, int32_t base, char **ppResult );
int32_t decimal(char *pExpr, int32_t *num, int32_t *carry);
