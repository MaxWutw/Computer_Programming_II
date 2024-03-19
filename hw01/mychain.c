#include "mychain.h"
// typedef struct _sPoly{
//     uint32_t size;
//     uint32_t *pPowers;
//     int32_t *pCoefficients;
// } sPoly;

int32_t chain_rule ( sPoly *pResult , const sPoly *pFy , const sPoly *pFx ){
    sPoly d_pFy, d_pFx;
    d_pFy.pCoefficients = (int32_t*)malloc(sizeof(int32_t) * pFy->size);
    d_pFy.pPowers = (uint32_t*)malloc(sizeof(uint32_t) * pFy->size);
    d_pFx.pCoefficients = (int32_t*)malloc(sizeof(int32_t) * pFx->size);
    d_pFx.pPowers = (uint32_t*)malloc(sizeof(uint32_t) * pFx->size);
    // copy
    d_pFy.size = pFy->size;
    d_pFx.size = pFx->size;
    for(int32_t i = 0;i < pFy->size;i++){
        d_pFy.pPowers[i] = pFy->pPowers[i];
        d_pFy.pCoefficients[i] = pFy->pCoefficients[i];
    }
    for(int32_t i = 0;i < pFx->size;i++){
        d_pFx.pPowers[i] = pFx->pPowers[i];
        d_pFx.pCoefficients[i] = pFx->pCoefficients[i];
    }
    sort(&d_pFx, d_pFx.size);
    sort(&d_pFy, d_pFy.size);
    sPoly dx, dy;
    dy.pCoefficients = (int32_t*)malloc(sizeof(int32_t) * pFy->size);
    dy.pPowers = (uint32_t*)malloc(sizeof(uint32_t) * pFy->size);
    dx.pCoefficients = (int32_t*)malloc(sizeof(int32_t) * pFx->size);
    dx.pPowers = (uint32_t*)malloc(sizeof(uint32_t) * pFx->size);
    unique(&d_pFx, &dx);
    unique(&d_pFy, &dy);
    for(int32_t i = 0;i < d_pFy.size;i++){
        d_pFy.pCoefficients[i] = d_pFy.pCoefficients[i] * d_pFy.pPowers[i];
        if(d_pFy.pPowers[i] <= 0) continue;
        else d_pFy.pPowers[i] -= 1;
    }
    for(int32_t i = 0;i < d_pFx.size;i++){
        d_pFx.pCoefficients[i] = d_pFx.pCoefficients[i] * d_pFx.pPowers[i];
        if(d_pFx.pPowers[i] <= 0) continue;
        else d_pFx.pPowers[i] -= 1;
    }
    for(int32_t i = 0;i < dy.size;i++){
        printf("%d ", dy.pPowers[i]);
    }
    // pResult->pPowers = (uint32_t *)malloc(sizeof(uint32_t));
    // for(int32_t i = 0;i < d_pFy.size;i++){
    //     for(int32_t j = 0;j < pFx->size;j++){
    //         pFx->pCoefficients[i];
    //     }
    // }

    return 0;
}


void sort(sPoly *data, int32_t size){
    for(int32_t i = 0;i < size;i++){
        for(int32_t j = 0;j < size - i - 1;j++){
            if(data->pPowers[j] < data->pPowers[j + 1]){
                int32_t tmp = data->pPowers[j];
                data->pPowers[j] = data->pPowers[j + 1];
                data->pPowers[j + 1] = tmp;

                int32_t tmp2 = data->pCoefficients[j];
                data->pCoefficients[j] = data->pCoefficients[j + 1];
                data->pCoefficients[j + 1] = tmp2;
            }
        }
    }
}

void unique(sPoly *src, sPoly *des){
    des->pCoefficients[0] = src->pCoefficients[0];
    des->pPowers[0] = src->pPowers[0];
    int32_t pow_idx = 0;
    for(int32_t i = 1;i < src->size;i++){
        if(src->pPowers[i] == des->pPowers[pow_idx]){
            des->pCoefficients[pow_idx] = des->pCoefficients[pow_idx] + src->pCoefficients[i];
        }
        else{
            pow_idx++;
            des->pPowers[pow_idx] = src->pPowers[i];
            des->pCoefficients[pow_idx] = src->pCoefficients[i];
        }
    }
    des->size = pow_idx + 1;
}