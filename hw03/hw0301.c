#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
int32_t str2int(char *str){
    char tmp[500];
    int32_t idx = 0;
    for(const char *it = str;*it != ',';it++){
        tmp[idx] = *it;
        idx++;
    }
    tmp[idx] = '\0';
    int32_t res = 0;
    for(int32_t i = 0;i < idx;i++){
        res += (res * 10) + (tmp[i] - '0');
    }
    return res;
}
int main(){
    freopen("out", "w", stdout);
    FILE *pFile;
    if((pFile = fopen("bible.txt", "r")) == NULL){
        fprintf(stderr, "File could not be opened!\n");
        return 0;
    }
    char search[500];
    printf("Please enter the search target: ");
    fgets(search, 500, stdin);
    int32_t search_len = strlen(search);
    for(int32_t i = 0;i < search_len;i++){
        search[i] = tolower(search[i]);
    }
    int32_t chapter = 0, verse = 0;
    char term[512], ver[50];
    char *token;
    int32_t cnt = 1;
    while(!feof(pFile)){
        char buffer[1024], tmp[1000];
        fgets(buffer, 1024, pFile);
        sscanf(buffer, "%*[^:]:%d,%*[^:]:%d,%*[^:]:\"%[^\"]\"%*[^:]:%*[^:]:\"%[^\"]\"%*s", &chapter, &verse, term, ver);
        search[search_len - 1] = '\0';
        char tmp_term[512];
        for(int32_t i = 0;i < strlen(term);i++){
            tmp_term[i] = tolower(term[i]);
        }
        tmp_term[strlen(term)] = '\0';
        if(strstr(tmp_term, search) != NULL){
            cnt++;
            // printf("Found %d time(s)\n", cnt);
            // printf("%d. %s %d:%d %s\n", cnt++, term, chapter, verse, ver);
        }
    }
    fseek(pFile, 0, SEEK_SET);
    printf("Found %d time(s)\n", cnt - 1);
    int32_t idx = 1;
    while(!feof(pFile)){
        char buffer[1024], tmp[1000];
        fgets(buffer, 1024, pFile);
        sscanf(buffer, "%*[^:]:%d,%*[^:]:%d,%*[^:]:\"%[^\"]\"%*[^:]:%*[^:]:\"%[^\"]\"%*s", &chapter, &verse, term, ver);
        search[search_len - 1] = '\0';
        char tmp_term[512];
        for(int32_t i = 0;i < strlen(term);i++){
            tmp_term[i] = tolower(term[i]);
        }
        tmp_term[strlen(term)] = '\0';
        if(strstr(tmp_term, search) != NULL){
            // printf("%d. %s %d:%d %s\n", idx++, term, chapter, verse, ver);
            printf("%d. %s %d:%d %s\n", idx++, ver, chapter, verse, term);
        }
    }

    return 0;
}