#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int32_t decimal(char *pExpr, int32_t start, int32_t end, int32_t *num, int32_t *carry);

int32_t calculate( char *pExpr, int32_t base, char **ppResult ){
    //還沒malloc、把數字轉換為X進位
    int32_t store_number[100] = {0}; //把數字存起來
    int32_t store_cal[100] = {1};//存符號（第一個index == 1）
    int32_t len = strlen(pExpr);
    if (len > 100 || len < 3){
        return -1;
    }
    //input will be "BEEF_16 * 00001_2"
    int32_t i = 0; //數string 的index
    int32_t index = 0; //operand 的尾巴
    int32_t num, carry = 0; //num 位數 carry 進位
    int32_t number = 0; //存數字和符號的index

    //限制格式
    if (pExpr[0] < 48 || (pExpr[0] > 57 && pExpr[0] < 65) || pExpr[0] > 70){
        return -1;
    }
    if (pExpr[len-1] < 48 || (pExpr[len-1] > 57 && pExpr[len-1] < 65) || pExpr[len-1] > 70){
        return -1;
    }

    while (pExpr[i] != '\0'){
        if (pExpr[i] == ' ' || i == len-1){
            if (i-index <= 2){
                index = i+1;
                i++;
                continue;
            }
            if (i == len-1){
                i++;
            }
            store_number[number] = decimal(pExpr, index, i-1, &num, &carry); //index是開頭 i是結尾
            if (store_number[number] == -1){
                return -1;
            }
            //printf("%d %d %d %d\n", index, i-1, number, store_number[number]);
            index = i+1;
            number++;
        }
        if (pExpr[i] == '*'){
            store_cal[number] = 2;
        }
        else if (pExpr[i] == '+'){
            store_cal[number] = 1;
        }
        else if (pExpr[i] == '-'){
            store_cal[number] = -1;
        }
        i++;
    }

    for (int32_t j = 0; j < number; j++){
        //printf("%d %d %d\n", store_cal[j], store_number[j], j);
        if (store_cal[j] == 2){
            store_number[j] *= store_number[j-1];
            store_number[j-1] = 0;
            store_cal[j] = store_cal[j-1];
        }
        //前面的數換成0 乘號換成加法 後面的數為兩者相乘
    }
    int32_t total = store_number[0];
    for (int32_t j = 0; j < number; j++){
        if (store_cal[j] == 1){
            total += store_number[j];
        }
        else if (store_cal[j] == -1){
            total -= store_number[j];
        }
    }
    if (total > 2147483647 || total < -2147483647){
        return -1;
    }
    //printf("%d\n", total);

    char RETURN[100] = {0};
    int32_t times = 0;
    if (total == 0){
        RETURN[0] = '0';
        times++;
    }
    int32_t check = 0;
    if (total < 0){
        total = -total;
        check = 1;
    }
    while(total != 0){
        if (total % base < 10){
            RETURN[times] = total % base + 48;
        }
        else if (total % base >= 10){
            RETURN[times] = total % base + 55;
        }
        // printf("%c %d\n", RETURN[times], times);
        total /= base;
        times++;
    }
    if (check == 1){
        times++;
        RETURN[times-1] = '-';
    }
    char TEMP[times];
    for (int32_t j = 0; j < times; j++){
        TEMP[j] = RETURN[j];
    }
    for (int32_t j = times-1; j >= 0; j--){
        RETURN[j] = TEMP[times-j-1];
    }
    RETURN[times] = '_';
    if (base >= 10){
        RETURN[times+1] = base / 10 + 48;
        RETURN[times+2] = base % 10 + 48;
    }
    else{
        RETURN[times+1] = base +48;
    }
    printf("%s\n", RETURN);// 就是這裡有問題！
    *ppResult = RETURN;
    //*ppResult = (char *)malloc(times * sizeof(char)); how to allocate??
    return 0;
}

int32_t decimal(char *pExpr, int32_t start, int32_t end, int32_t *num, int32_t *carry){
    for (int32_t i = start; i <= end; i++){
        if (pExpr[i] == '_'){
            *num = i;
            break;
        }
    }
    //printf("%d\n", end-*num);
    if (end-*num == 1){
        *carry = (pExpr[*num+1]-'0');
    }
    else if (end-*num == 2){
        *carry = 10*(pExpr[*num+1]-'0') + (pExpr[*num+2]-'0');
    }
    else{
        return -1;
    }
    if (*carry < 2 || *carry > 16){
        return -1;
    }
    //printf("%d %d\n", *num-start, *carry);

    //turn into dec
    int32_t digits = 0;
    for (int32_t i = 0; i < *num-start; i++){
        if (pExpr[start+i] >= 48 && pExpr[start+i] <= 57){
            digits += pow(*carry, *num-start-i-1) * (pExpr[start+i]-'0');
        }
        else if (pExpr[start+i] >= 65 && pExpr[start+i] <= 70){
            digits += pow(*carry, *num-start-i-1) * (pExpr[start+i]-55);
        }
        else{
            return -1;
        }
    }
    //printf("%d\n", digits);
    return digits;
}
