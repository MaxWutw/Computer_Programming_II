#include "mystring.h"

char *mystrchr(const char *s, int c){
    if(!s) return NULL;
    while(*s != 0){
        if(*s == c) return (char *)s;
        s++;
    }
    return NULL;
}
char *mystrrchr(const char *s, int c){
    if(!s) return NULL;
    int32_t leng = 0;
    const char *s_tmp = s;
    while(*s_tmp != 0){
        leng++;
        s_tmp++;
    }
    for(const char *it = s + leng;it != s;it--){
        if(*it != c) continue;
    }
    return NULL;
}
size_t mystrspn(const char *s, const char *accept){
    int32_t leng = 0;
    int8_t judge = 0;
    if(!s || !accept) return 0;
    for(const char *it = s;*it != 0;it++){
        for(const char *iter = accept;*iter != 0;iter++){
            if(*it == *iter){
                judge = 1;
                leng++;
                break;
            }
        }
        if(!judge) break;
        judge = 0;
    }
    return leng;
}

size_t mystrcspn(const char *s, const char *reject){
    if(!s || !reject) return 0;
    int32_t leng = 0;
    for(const char *it = s;*it != 0;it++, leng++){
        for(const char *iter = reject;*iter != 0;iter++){
            if(*it == *iter) return leng;
        }
    }
    return leng;
}
char *mystrpbrk(const char *s, const char *accept){
    if(!s || !accept) return NULL;
    for(const char *it = s;*it != 0;it++){
        for(const char *iter = accept;*iter != 0;iter++){
            if(*it == *iter) return (char *)it;
        }
    }
    return NULL;
}
char *mystrstr(const char *haystack, const char *needle){
    if(!haystack || !needle) return NULL;
    int8_t judge = 1;
    const char *iter = needle;
    const char *start = NULL;
    for(const char *it = haystack;*it != 0;it++){
        if(*iter == 0) return (char *)start;
        if(*iter == *it && !start) start = it;
        if(*iter == *it) iter++;
        else if(*iter != *it){
            iter = needle;
            start = NULL;
        }
    }
    return NULL;
}
char *mystrtok(char *str, const char *delim){
    static char* idx = NULL;
    if(str == NULL){
        str = idx;
        if(idx == NULL) return NULL;
    }
    char *tmp = mystrpbrk(str, delim);
    if(tmp){
        *tmp = 0;
        idx = tmp + 1;
    }
    else idx = NULL;
    return str;
}