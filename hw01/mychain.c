#include "mychain.h"

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
    // for(int32_t i = 0;i < d_pFx.size;i++) printf("%d ", d_pFx.pCoefficients[i]);
    // printf("\n");
    sort(&d_pFx, d_pFx.size);
    sort(&d_pFy, d_pFy.size);
    sPoly dx, dy;
    dy.pCoefficients = (int32_t*)malloc(sizeof(int32_t) * pFy->size);
    dy.pPowers = (uint32_t*)malloc(sizeof(uint32_t) * pFy->size);
    dx.pCoefficients = (int32_t*)malloc(sizeof(int32_t) * pFx->size);
    dx.pPowers = (uint32_t*)malloc(sizeof(uint32_t) * pFx->size);
    unique(&d_pFx, &dx);
    unique(&d_pFy, &dy);
    // printf("*************************\n");
    // for(int32_t i = 0;i < dx.size;i++){
    //     printf("%d ", dx.pPowers[i]);
    // }
    // printf("\n");
    // for(int32_t i = 0;i < dx.size;i++) printf("%d ", dx.pCoefficients[i]);
    // printf("\n");
    // printf("*************************\n");
    sPoly first_dx, first_dy;
    first_dy.pCoefficients = (int32_t*)malloc(sizeof(int32_t) * dy.size);
    first_dy.pPowers = (uint32_t*)malloc(sizeof(uint32_t) * dy.size);
    first_dx.pCoefficients = (int32_t*)malloc(sizeof(int32_t) * dx.size);
    first_dx.pPowers = (uint32_t*)malloc(sizeof(uint32_t) * dx.size);
    first_dy.size = dy.size;
    first_dx.size = dx.size;
    for(int32_t i = 0;i < dy.size;i++){
        first_dy.pPowers[i] = dy.pPowers[i];
        first_dy.pCoefficients[i] = dy.pCoefficients[i];
    }
    for(int32_t i = 0;i < dx.size;i++){
        first_dx.pPowers[i] = dx.pPowers[i];
        first_dx.pCoefficients[i] = dx.pCoefficients[i];
    }

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
    // printf("size: %d\n", first_dy.pCoefficients[0]);
    // for(int32_t i = 0;i < dx.size;i++) printf("%d ", dx.pPowers[i]);
    // printf("\n");
    pResult->pCoefficients = (int32_t*)malloc(sizeof(int32_t) * 10000);
    pResult->pPowers = (uint32_t*)calloc(10000, sizeof(uint32_t));
    pResult->size = 1;
    pResult->pCoefficients[0] = 1;
    // cal_times(&dx, first_dy.pPowers[0], first_dy.pCoefficients[0], &first_dx, pResult);
    // for(int32_t i = 0;i < dy.size;i++){
    //     printf("%d ", dy.pPowers[i]);
    // }

    // for(int32_t i = 0;i < d_pFy.size;i++){
    //     for(int32_t j = 0;j < pFx->size;j++){
    //         pFx->pCoefficients[i];
    //     }
    // }
    // sPoly tmp_data, store;
    // tmp_data.pCoefficients = (int32_t*)malloc(sizeof(int32_t));
    // tmp_data.pPowers = (uint32_t*)calloc(1, sizeof(uint32_t));
    // tmp_data.pCoefficients[0] = 1;
    // tmp_data.size = 1;
    sPoly store;
    store.pCoefficients = (int32_t*)malloc(sizeof(int32_t) * 10000);
    store.pPowers = (uint32_t*)calloc(10000, sizeof(uint32_t));
    store.size = 0;
    int32_t idx_leng = 0;
    for(int32_t i = 0;i < first_dy.size;i++){
        sPoly tmp_data;
        tmp_data.pCoefficients = (int32_t*)malloc(sizeof(int32_t));
        tmp_data.pPowers = (uint32_t*)calloc(1, sizeof(uint32_t));
        tmp_data.pCoefficients[0] = 1;
        tmp_data.size = 1;
        // printf("djskfljasdklf: %d\n", first_dy.pPowers[i]);
        cal_times(&dx, first_dy.pPowers[i], first_dy.pCoefficients[i], &first_dx, &tmp_data);
        store.size += tmp_data.size;
        for(int32_t i = 0;i < tmp_data.size;i++){
            store.pPowers[idx_leng] = tmp_data.pPowers[i];
            store.pCoefficients[idx_leng] = tmp_data.pCoefficients[i];
            idx_leng++;
        }
        // printf("\n**************************\n");
        // for(int32_t i = 0;i < store.size;i++){
        //     printf("%d ", store.pPowers[i]);
        // }
        // printf("\n");
        // for(int32_t i = 0;i < store.size;i++){
        //     printf("%d ", store.pCoefficients[i]);
        // }
        // printf("\n**************************\n");
        free(tmp_data.pCoefficients);
        free(tmp_data.pPowers);
        
    }
    // cal_times(&dx, first_dy.pPowers[0], first_dy.pCoefficients[0], &first_dx, &tmp_data);
    sort(&store, store.size);
    unique(&store, pResult);
    // printf("\n===========\n");
    // for(int32_t i = 0;i < pResult->size;i++){
    //     printf("%d ", pResult->pPowers[i]);
    // }
    // printf("\n");
    // for(int32_t i = 0;i < pResult->size;i++){
    //     printf("%d ", pResult->pCoefficients[i]);
    // }
    // printf("\n");
    free(d_pFy.pCoefficients);
    free(d_pFy.pPowers);
    free(d_pFx.pCoefficients);
    free(d_pFx.pPowers);
    free(dx.pCoefficients);
    free(dx.pPowers);
    free(dy.pCoefficients);
    free(dy.pPowers);
    free(first_dx.pCoefficients);
    free(first_dx.pPowers);
    free(first_dy.pCoefficients);
    free(first_dy.pPowers);
    free(store.pCoefficients);
    free(store.pPowers);

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
    // des->pCoefficients[0] = src->pCoefficients[0];
    // des->pPowers[0] = src->pPowers[0];
    int32_t pow_idx = 0;
    int8_t judge = 1;
    for(int32_t i = 0;i < src->size;i++){
        if(src->pCoefficients[i] == 0) continue;
        if(judge){
            des->pCoefficients[pow_idx] = src->pCoefficients[i];
            des->pPowers[pow_idx] = src->pPowers[i];
            judge = 0;
            continue;
        }
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

void cal_times(sPoly *src, int32_t times, int32_t base, sPoly *chain, sPoly *des){
    int32_t leng = 1;
    for(int32_t i = 0;i < times;i++) leng *= src->size;
    // printf("%d\n", chain->size);
    int32_t chain_sz = 0;
    if(chain->pPowers[chain->size - 1] == 0){
        leng *= (chain->size - 1);
        chain_sz = chain->size - 1;
    }
    else{
        leng *= chain->size;
        chain_sz = chain->size;
    }
    // printf("%d\n", leng);

    if(des->size < leng){
        des->pCoefficients = (int32_t*)realloc(des->pCoefficients, sizeof(int32_t) * leng);
        des->pPowers = (uint32_t*)realloc(des->pPowers, sizeof(uint32_t) * leng);
        des->size = leng;
    }

    sPoly tmp;
    tmp.pCoefficients = (int32_t*)calloc(leng, sizeof(int32_t));
    tmp.pPowers = (uint32_t*)calloc(leng, sizeof(uint32_t));
    tmp.size = leng;
    int32_t idx = 0, dynamic_leng = 1;
    // printf("times: %d\n", times);
    for(int32_t k = 0;k < times;k++){
        for(int32_t i = 0;i < dynamic_leng;i++){
            for(int32_t j = 0;j < src->size;j++){
                tmp.pPowers[idx] = des->pPowers[i] + src->pPowers[j];
                tmp.pCoefficients[idx] = des->pCoefficients[i] * src->pCoefficients[j];
                idx++;
            }
        }
        dynamic_leng = idx;
        idx = 0;
        for(int32_t it = 0;it < dynamic_leng;it++){
            des->pPowers[it] = tmp.pPowers[it];
            des->pCoefficients[it] = tmp.pCoefficients[it];
        }
        // printf("dynamic: %d\n", dynamic_leng);
    }
    // printf("chain size: %d\n", dynamic_leng);
    // printf("=====================\n");
    // for(int32_t i = 0;i < des->size;i++){
    //     printf("%d ", des->pPowers[i]);
    // }
    // printf("\n");
    // for(int32_t i = 0;i < des->size;i++){
    //     printf("%d ", des->pCoefficients[i]);
    // }
    // printf("\n");
    // printf("=====================\n");
    // for(int32_t i = 0;i < des->size;i++){
    //     printf("%d ", des->pPowers[i]);
    // }
    // printf("\n");
    // for(int32_t i = 0;i < des->size;i++){
    //     printf("%d ", des->pCoefficients[i]);
    // }
    // printf("\n");
    idx = 0;
    for(int32_t i = 0;i < chain_sz;i++){
        for(int32_t j = 0;j < dynamic_leng;j++){
            tmp.pPowers[idx] = des->pPowers[j] + chain->pPowers[i];
            tmp.pCoefficients[idx] = des->pCoefficients[j] * chain->pCoefficients[i];
            idx++;
            // printf("tmp: %d\n", tmp.pCoefficients[idx - 1]);
            // printf("dsf");
        }
    }
    // for(int32_t it = 0;it < dynamic_leng;it++){
    //     des->pPowers[it] = tmp.pPowers[it];
    //     des->pCoefficients[it] = tmp.pCoefficients[it];
    // }
    dynamic_leng = idx;
    for(int32_t it = 0;it < dynamic_leng;it++){
        des->pPowers[it] = tmp.pPowers[it];
        des->pCoefficients[it] = tmp.pCoefficients[it] * base;
    }
    // printf("\n=========================\n");
    // for(int32_t i = 0;i < des->size;i++){
    //     printf("%d ", des->pPowers[i]);
    // }
    // printf("\n");
    // for(int32_t i = 0;i < des->size;i++){
    //     printf("%d ", des->pCoefficients[i]);
    // }
    // printf("\n=========================\n");
    free(tmp.pCoefficients);
    free(tmp.pPowers);
}