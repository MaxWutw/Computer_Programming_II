#include "mychain.h"
// typedef struct _sPoly{
//     uint32_t size;
//     uint32_t *pPowers;
//     int32_t *pCoefficients;
// } sPoly;

int32_t chain_rule ( sPoly *pResult , const sPoly *pFy , const sPoly *pFx ){
    sPoly d_pFy = pFy, d_pFx = pFx;
    for(int32_t i = 0;i < d_pFy.size;i++){
        d_pFy.pCoefficients[i] = d_pFy.pCoefficients[i] * d_pFy.pPowers[i];
        d_pFy.pPowers[i] -= 1;
    }
    for(int32_t i = 0;i < d_pFx.size;i++){
        d_pFx.pCoefficients[i] = d_pFx.pCoefficients[i] * d_pFx.pPowers[i];
        d_pFx.pPowers[i] -= 1;
    }

    return 0;
}