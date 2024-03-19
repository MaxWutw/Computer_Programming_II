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
    sPoly first_dx, first_dy;
    first_dy.pCoefficients = (int32_t*)malloc(sizeof(int32_t) * dy.size);
    first_dy.pPowers = (uint32_t*)malloc(sizeof(uint32_t) * dy.size);
    first_dx.pCoefficients = (int32_t*)malloc(sizeof(int32_t) * dx.size);
    first_dx.pPowers = (uint32_t*)malloc(sizeof(uint32_t) * dx.size);
    first_dy.size = dy.size;
    first_dx.size = dx.size;

    for(int32_t i = 0;i < first_dy.size;i++){
        first_dy.pCoefficients[i] = first_dy.pCoefficients[i] * first_dy.pPowers[i];
        if(first_dy.pPowers[i] <= 0) continue;
        else first_dy.pPowers[i] -= 1;
    }
    for(int32_t i = 0;i < first_dx.size;i++){
        first_dx.pCoefficients[i] = first_dx.pCoefficients[i] * first_dx.pPowers[i];
        if(first_dx.pPowers[i] <= 0) continue;
        else first_dx.pPowers[i] -= 1;
    }
    printf("size: %d\n", first_dy.pPowers[0]);
    // for(int32_t i = 0;i < dx.size;i++) printf("%d ", dx.pPowers[i]);
    // printf("\n");
    cal_times(&dx, first_dy.pPowers[0], first_dy.pCoefficients[0], &first_dx);
    // for(int32_t i = 0;i < dy.size;i++){
    //     printf("%d ", dy.pPowers[i]);
    // }
    // pResult->pPowers = (uint32_t *)malloc(sizeof(uint32_t));
    // for(int32_t i = 0;i < d_pFy.size;i++){
    //     for(int32_t j = 0;j < pFx->size;j++){
    //         pFx->pCoefficients[i];
    //     }
    // }
    // for(int32_t i = 0;i < first_dy.size;i++){
    //     cal_times(&px, first_dy->pPowers[i], first_dy->pCoefficients[i], &first_dx);
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

void cal_times(sPoly *src, int32_t times, int32_t base, sPoly *chain){
    int32_t leng = src->size * src->size * chain->size;
    for(int32_t i = 0;i < times;i++) leng *= src->size;
    leng *= chain->size;
    printf("%d\n", leng);
    sPoly tmp;
    tmp.pCoefficients = (int32_t*)calloc(leng, sizeof(int32_t));
    tmp.pPowers = (uint32_t*)calloc(leng, sizeof(uint32_t));
    tmp.size = leng;
    for(int32_t i = 0;i < src->size;i++){
        tmp.pCoefficients[i] = 1;
    }

    int32_t idx = 0, dynamic_leng = src->size;
    for(int32_t k = 0;k < times;k++){
        for(int32_t i = 0;i < dynamic_leng;i++){
            for(int32_t j = 0;j < src->size;j++){
                tmp.pPowers[idx] = tmp.pPowers[i] + src->pPowers[j];
                tmp.pCoefficients[idx] = tmp.pCoefficients[i] * src->pCoefficients[j];
                idx++;
            }
        }
        dynamic_leng = idx;
    }
    for(int32_t i = 0;i < dynamic_leng;i++){
        printf("%d ", tmp.pPowers[i]);
    }
    printf("\n");
    for(int32_t i = 0;i < dynamic_leng;i++){
        printf("%d ", tmp.pCoefficients[i]);
    }
}