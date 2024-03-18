#include <stdio.h>
#include <stdlib.h>
#include "mychain.h"
int main(){
    // uint32_t size;
    // uint32_t pPowers[] = {};
    // int32_t *pCoefficients;
    sPoly pResult, pFy, pFx;
    pFy.size = 1;
    pFy.pPowers = malloc(sizeof(int) * 1);
    pFy.pCoefficients = malloc(sizeof(int) * 1);
    pFy.pPowers[0] = 2;
    pFy.pCoefficients[0] = 1;

    pFx.pPowers = malloc(sizeof(int) * 2);
    pFx.pCoefficients = malloc(sizeof(int) * 2);
    pFx.pPowers[0] = 1;
    pFx.pPowers[1] = 0;
    pFx.pCoefficients[0] = 32;
    pFx.pCoefficients[1] = -24;

    chain_rule(&pResult, &pFy, &pFx);

    return 0;
}
