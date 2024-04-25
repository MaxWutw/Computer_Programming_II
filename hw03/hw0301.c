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
    char term[50];
    char *token;
    int32_t cnt = 1;
    while(!feof(pFile)){
        char buffer[500];
        fgets(buffer, 500, pFile);
        token = strtok(buffer, ":");
        token = strtok(NULL, ":");
        chapter = str2int(token);
        // printf("%d\n", chapter);
        token = strtok(NULL, ":");
        verse = str2int(token);
        // printf("%d %d\n", chapter, verse);
        // token = strtok(NULL, ":");
        token = strtok(NULL, "\"");
        // printf("%s\n", token);
        // break;
        int8_t correct = 1;
        // printf("%s\n", search);
        // printf("%s\n", token);
        for(int32_t i = 0;i < strlen(token);i++){
            for(int32_t j = 0;j < search_len - 1;j++){
                if(search[j] == tolower(token[i + j])){
                    continue;
                }
                else{
                    correct = 0;
                    break;
                }
            }
            if(correct){
                char tmp[500];
                for(int32_t i = 0;i < strlen(token);i++) tmp[i] = token[i];
                tmp[strlen(token)] = '\0';
                token = strtok(NULL, ":");
                token = strtok(NULL, ":");
                token = strtok(NULL, "\"");
                printf("%s\n", token);
                printf("Found %d time(s)\n", cnt);
                printf("%d. %s %d:%d %s\n", cnt++, token, chapter, verse, tmp);
            }
        }
        break;
    }

    return 0;
}