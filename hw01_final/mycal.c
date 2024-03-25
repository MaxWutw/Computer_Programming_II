#include "mycal.h"

int32_t calculate(char *pEpr, int32_t base, char **ppResult){
    int64_t sum = 0;
    // if(!valid(pEpr)){
    //     return -1;
    // }
    if(pEpr[0] == '+' || pEpr[0] == '-' || pEpr[0] == '*') return -1;
    if(!pEpr) return -1;
    char *it = pEpr;
    int64_t stack[200], idx = 0;
    for(int32_t i = 0;i < 200;i++) stack[i] = 0;
    int8_t wrong = 0;
    stack[idx] = convert2base10(it, &wrong);
    if(wrong == 1) return -1;
    idx++;
    while(*it != 0){
        while(*it != ' ' && *it != 0) it++;
        if(*(it + 1) == '+'){
            it += 3;
            stack[idx++] = convert2base10(it, &wrong);
            if(wrong == 1) return -1;
        }
        else if(*(it + 1) == '-'){
            it += 3;
            stack[idx++] = -convert2base10(it++, &wrong);
            if(wrong == 1) return -1;
        }
        else if(*(it + 1) == '*'){
            it += 3;
            int64_t tmp = convert2base10(it, &wrong);
            if(wrong == 1) return -1;
            stack[idx - 1] = stack[idx - 1] * tmp;
        }
    }
    for(int i = 0;i < 200;i++) sum += stack[i];
    // printf("%d\n", sum);
    int64_t quotient = (sum < 0 ? -sum : sum), remainder;
    char number[105], answer[105];
    int64_t leng = 0;
    while(quotient != 0){
        remainder = quotient % base;
        if(remainder < 10) number[leng++] = remainder + '0';
        else number[leng++] = remainder + 'A' - 10;
        quotient = quotient / base;
    }
    if(sum < 0) number[leng++] = '-';
    
    for(int32_t i = 0;i < leng;i++) answer[i] = number[leng - i - 1];
    answer[leng] = '_';
    int64_t num = base;
    char tmp[10];
    int64_t tmp_len = 0;
    while(num){
        // answer[++leng] = '0' + num % 10;
        tmp[tmp_len++] = '0' + num % 10;
        num /= 10;
    }
    for(int32_t i = 0;i < tmp_len;i++) answer[++leng] = tmp[tmp_len - i - 1];
    answer[++leng] = 0;
    *ppResult = (char*)malloc(sizeof(char) * leng);
    // *ppResult = answer;
    // for(int32_t i = 0;i <= leng;i++) *ppResult[i] = answer[i];
    // *ppResult[leng] = 'a';
    // printf("char: %c\n", *ppResult[0]);
    strcpy(*ppResult, answer);
    // printf("%p %p\n", &ppResult, answer);
    // printf("%s\n", *ppResult);

    return 0;
}

int64_t convert2base10(char *data, int8_t *wrong){
    int64_t base = 0, sum = 0, judge = 1;
    int64_t maxi_char = '0';
    for(char *it = data;*it != 0 && *it != ' ';it++){
        if(*it == '_'){
            judge = 0;
            it++;
            while(*it != 0 && *it != ' '){
                base = (*it - '0') + (base * 10);
                it++;
            }
        }
        if(*it > maxi_char && judge) maxi_char = *it;
    }
    if(base < 10){ 
        if(maxi_char - '0' >= base){
            *wrong = 1;
            return 0;
        }
    }
    else if(base > 10){
        if(maxi_char - 'A' + 10 >= base){
            *wrong = 1;
            return 0;
        }
    }
    for(char *it = data;*it != '_';it++){
        if(*it >= 'A' && *it <= 'F') sum = (*it - 'A' + 10) + (sum * base);
        else sum = (*it - '0') + (sum * base);
    }
    return sum;
}

// int8_t valid(const char* str){
//     int64_t space = 0, op = 0;
//     for(const char* i = str;*i != 0;i++){
//         if(*i == ' ') space++;
//         else if(*i == '+' || *i == '-' || *i == '*') op++;
//     }
//     return (space == op * 2 ? 1 : 0);
// }