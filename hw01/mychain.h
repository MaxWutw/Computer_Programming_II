#ifndef _MYCHAIN_H_
#define _MYCHAIN_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct _sPoly{
    uint32_t size;
    uint32_t *pPowers;
    int32_t *pCoefficients;
} sPoly;
int32_t chain_rule ( sPoly *pResult , const sPoly *pFy , const sPoly *pFx );
void sort(sPoly *data, int32_t size);
void unique(sPoly *src, sPoly *des);
void cal_times(sPoly *src, int32_t times, int32_t base, sPoly *chain);

#endif