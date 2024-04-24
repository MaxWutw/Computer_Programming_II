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
        printf("dfs");
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
    FILE *pFile;
    if((pFile = fopen("bible.txt", "r")) == NULL){
        fprintf(stderr, "File could not be opened!\n");
        return 0;
    }
    char search[500];
    printf("Please enter the search target: ");
    fgets(search, 500, stdin);
    int32_t search_len = strlen(search);
    for(int32_t i = 0;i < search_len;i){
        search[i] = tolower(search[i]);
    }
    int32_t chapter = 0, verse = 0;
    while(!feof(pFile)){
        char buffer[500];
        fgets(buffer, 500, pFile);
        strtok(":", buffer);
        chapter = str2int(buffer);
        printf("%d\n", chapter);
        break;
        strtok(":", NULL);
        int8_t correct = 0;
        for(int32_t i = 0;i < strlen(buffer);i++){
            for(int32_t j = 0;j < search_len;j++){
                // if(search[j] == buffer[i])
            }
        }
    }

    return 0;
}