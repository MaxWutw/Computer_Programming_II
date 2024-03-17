#include "mycal.h"

int32_t calculate(char *pEpr, int32_t base, char **ppResult){
    int32_t sum = 0;
    if(pEpr[0] == '+' || pEpr[0] == '-' || pEpr[0] == '*') return 0;
    if(!pEpr) return 0;
    char *it = pEpr;
    int32_t stack[200], idx = 0;
    for(int32_t i = 0;i < 200;i++) stack[i] = 0;
    stack[idx] = convert2base10(it);
    idx++;
    while(*it != 0){
        while(*it != ' ' && *it != 0) it++;
        if(*(it + 1) == '+'){
            it += 3;
            stack[idx++] = convert2base10(it);
        }
        else if(*(it + 1) == '-'){
            it += 3;
            stack[idx++] = -convert2base10(it++);
        }
        else if(*(it + 1) == '*'){
            it += 3;
            int32_t tmp = convert2base10(it);
            stack[idx - 1] = stack[idx - 1] * tmp;
        }
    }
    for(int i = 0;i < 200;i++) sum += stack[i];
    printf("%d\n", sum);
    int32_t quotient = abs(sum), remainder;
    char number[105], answer[105];
    int32_t leng = 0;
    while(quotient != 0){
        remainder = quotient % base;
        if(remainder < 10) number[leng++] = remainder + '0';
        else number[leng++] = remainder + 'A' - 10;
        quotient = quotient / base;
    }
    if(sum < 0) number[leng++] = '-';
    *ppResult = (char*)malloc(sizeof(char) * leng);
    for(int32_t i = 0;i < leng;i++) answer[i] = number[leng - i - 1];
    answer[leng] = '_';
    int32_t num = base;
    char tmp[10];
    int32_t tmp_len = 0;
    while(num){
        // answer[++leng] = '0' + num % 10;
        tmp[tmp_len++] = '0' + num % 10;
        num /= 10;
    }
    for(int32_t i = 0;i < tmp_len;i++) answer[++leng] = tmp[tmp_len - i - 1];
    answer[++leng] = 0;
    *ppResult = answer;
    printf("%s\n", *ppResult);

    return 1;
}

int32_t convert2base10(char *data){
    int32_t base = 0;
    int32_t sum = 0;
    for(char *it = data;*it != 0 && *it != ' ';it++){
        if(*it == '_'){
            it++;
            while(*it != 0 && *it != ' '){
                base = (*it - '0') + (base * 10);
                it++;
            }
        }
    }
    for(char *it = data;*it != '_';it++){
        if(*it >= 'A' && *it <= 'F') sum = (*it - 'A' + 10) + (sum * base);
        else sum = (*it - '0') + (sum * base);
    }
    return sum;
}

int32_t digit(int32_t num){
    int32_t ret = 0;
    while(num){
        num /= 10;
        ret++;
    }
    return ret;
}