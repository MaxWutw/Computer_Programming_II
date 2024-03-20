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
    pResult->pCoefficients = (int32_t*)malloc(sizeof(int32_t) * 10000);
    pResult->pPowers = (uint32_t*)calloc(10000, sizeof(uint32_t));
    pResult->size = 1;
    pResult->pCoefficients[0] = 1;
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
        cal_times(&dx, first_dy.pPowers[i], first_dy.pCoefficients[i], &first_dx, &tmp_data);
        store.size += tmp_data.size;
        for(int32_t i = 0;i < tmp_data.size;i++){
            store.pPowers[idx_leng] = tmp_data.pPowers[i];
            store.pCoefficients[idx_leng] = tmp_data.pCoefficients[i];
            idx_leng++;
        }
        free(tmp_data.pCoefficients);
        free(tmp_data.pPowers);
        
    }
    sort(&store, store.size);
    unique(&store, pResult);
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
    int32_t chain_sz = 0;
    if(chain->pPowers[chain->size - 1] == 0){
        leng *= (chain->size - 1);
        chain_sz = chain->size - 1;
    }
    else{
        leng *= chain->size;
        chain_sz = chain->size;
    }
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
    }
    idx = 0;
    for(int32_t i = 0;i < chain_sz;i++){
        for(int32_t j = 0;j < dynamic_leng;j++){
            tmp.pPowers[idx] = des->pPowers[j] + chain->pPowers[i];
            tmp.pCoefficients[idx] = des->pCoefficients[j] * chain->pCoefficients[i];
            idx++;
        }
    }
    dynamic_leng = idx;
    for(int32_t it = 0;it < dynamic_leng;it++){
        des->pPowers[it] = tmp.pPowers[it];
        des->pCoefficients[it] = tmp.pCoefficients[it] * base;
    }
    free(tmp.pCoefficients);
    free(tmp.pPowers);
}