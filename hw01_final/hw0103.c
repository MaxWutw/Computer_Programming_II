// #include <stdio.h>
// #include <stdlib.h>
// #include "mychain.h"
// int main(){
//     // uint32_t size;
//     // uint32_t pPowers[] = {};
//     // int32_t *pCoefficients;
//     // sPoly pResult, pFy, pFx;
//     // pFy.size = 1;
//     // pFy.pPowers = malloc(sizeof(int) * 1);
//     // pFy.pCoefficients = malloc(sizeof(int) * 1);
//     // pFy.pPowers[0] = 2;
//     // pFy.pCoefficients[0] = 1;

//     // pFx.size = 2;
//     // pFx.pPowers = malloc(sizeof(int) * 2);
//     // pFx.pCoefficients = malloc(sizeof(int) * 2);
//     // pFx.pPowers[0] = 1;
//     // pFx.pPowers[1] = 0;
//     // pFx.pCoefficients[0] = 4;
//     // pFx.pCoefficients[1] = -3;


//     // sPoly pResult, pFy, pFx;
//     // pFy.size = 2;
//     // pFy.pPowers = malloc(sizeof(int) * 2);
//     // pFy.pCoefficients = malloc(sizeof(int) * 2);
//     // pFy.pPowers[0] = 3;
//     // pFy.pCoefficients[0] = 1;
//     // pFy.pPowers[1] = 2;
//     // pFy.pCoefficients[0] = 1;
    

//     // pFx.size = 3;
//     // pFx.pPowers = malloc(sizeof(int) * 3);
//     // pFx.pCoefficients = malloc(sizeof(int) * 3);
//     // pFx.pPowers[0] = 2;
//     // pFx.pPowers[1] = 1;
//     // pFx.pPowers[2] = 0;
//     // pFx.pCoefficients[0] = 4;
//     // pFx.pCoefficients[1] = 3;
//     // pFx.pCoefficients[2] = -1;


//     sPoly pResult, pFy, pFx;
//     pFy.size = 2;
//     pFy.pPowers = malloc(sizeof(int) * 2);
//     pFy.pCoefficients = malloc(sizeof(int) * 2);
//     pFy.pPowers[0] = 3;
//     pFy.pCoefficients[0] = 6;
//     pFy.pPowers[1] = 5;
//     pFy.pCoefficients[1] = 7;

//     pFx.size = 3;
//     pFx.pPowers = malloc(sizeof(int) * 3);
//     pFx.pCoefficients = malloc(sizeof(int) * 3);
//     pFx.pPowers[0] = 2;
//     pFx.pPowers[1] = 3;
//     pFx.pPowers[2] = 4;
//     pFx.pCoefficients[0] = 4;
//     pFx.pCoefficients[1] = 1;
//     pFx.pCoefficients[2] = 0;

//     chain_rule(&pResult, &pFy, &pFx);
//     free(pFy.pCoefficients);
//     free(pFy.pPowers);
//     free(pFx.pCoefficients);
//     free(pFx.pPowers);
//     free(pResult.pCoefficients);
//     free(pResult.pPowers);

//     return 0;
// }


#include "mychain.h"

int main()
{
    sPoly pFy;
    sPoly pFx;
    sPoly pResult;
    uint32_t y_size = 0;
    uint32_t x_size = 0;
    scanf("%d", &y_size);
    pFy.size = y_size;
    scanf("%d", &x_size);
    pFx.size = x_size;
    pFy.pPowers = (uint32_t *)malloc(y_size * sizeof(uint32_t));
    pFy.pCoefficients = (int32_t *)malloc(y_size * sizeof(int32_t));
    pFx.pPowers = (uint32_t *)malloc(x_size * sizeof(uint32_t));
    pFx.pCoefficients = (int32_t *)malloc(x_size * sizeof(int32_t));
    for (uint32_t i = 0; i < y_size; i++)
    {
        scanf("%d", &pFy.pPowers[i]);
    }
    for (uint32_t i = 0; i < y_size; i++)
    {
        scanf("%d", &pFy.pCoefficients[i]);
    }
    for (uint32_t i = 0; i < x_size; i++)
    {
        scanf("%d", &pFx.pPowers[i]);
    }
    for (uint32_t i = 0; i < x_size; i++)
    {
        scanf("%d", &pFx.pCoefficients[i]);
    }
    chain_rule(&pResult, &pFy, &pFx);
    printf("pResult.size = %d\n", pResult.size);
    for (uint32_t i = 0; i < pResult.size; i++)
    {
        printf("pResult.pPowers[%d] = %d\n", i, pResult.pPowers[i]);
        printf("pResult.pCoefficients[%d] = %d\n", i, pResult.pCoefficients[i]);
    }
    free(pResult.pPowers);
    free(pResult.pCoefficients);
    free(pFy.pPowers);
    free(pFy.pCoefficients);
    free(pFx.pPowers);
    free(pFx.pCoefficients);
    return 0;
}