#include "utility.h"

void remove_asterisks(char *str){
    char *src = str;
    char *dst = str;
    
    while (*src) {
        if (*src != '*') {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

int32_t trace(int8_t line_flag, int8_t code_flag, char *function_name, char* filename){
    int32_t cnt = 0;
    FILE *pFile;
    if((pFile = fopen(filename, "r")) == NULL){
        fprintf(stderr, "File could not be opened!\n");
        return 0;
    }
    while(!feof(pFile)){
        char buffer[500];
        fgets(buffer, 500, pFile);
        if(strstr(buffer, function_name) != NULL){
            cnt++;
        }
    }
    fseek(pFile, 0, SEEK_SET);
    printf("%s:\n", function_name);
    printf("  %s (count: %d)\n", filename, cnt);
    int32_t line_cnt = 0;
    while(!feof(pFile)){
        line_cnt++;
        char buffer[500];
        fgets(buffer, 500, pFile);
        buffer[strlen(buffer) - 1] = '\0';
        if(strstr(buffer, function_name) != NULL){
            if(line_flag || code_flag) printf("    ");
            if(line_flag)
                printf("line %d:", line_cnt);
            if(code_flag)
                printf("%s", buffer);
            printf("\n");
        }
    }
    return 1;
}

int32_t func(int8_t line_flag, int8_t code_flag, char *headername, char* filename){
    FILE *pFile, *hFile;
    if((pFile = fopen(filename, "r")) == NULL){
        fprintf(stderr, "File could not be opened!\n");
        return 0;
    }
    if((hFile = fopen(headername, "r")) == NULL){
        fprintf(stderr, "File could not be opened!\n");
        return 0;
    }
    char *func_arr[500];
    int32_t idx = 0, cnt = 0;
    char tmp1[100], tmp2[100];
    while(!feof(hFile)){
        char buffer[500];
        int32_t readcnt = 0;
        fgets(buffer, 500, hFile);
        readcnt = sscanf(buffer, "%*[^ ] %[*a-zA-Z0-9](%*[^(];", tmp1);
        // printf("%d\n", readcnt);
        // if(tmp1[0] == '\n' || tmp1[0] == '\0') continue;
        if(readcnt <= 0) continue;
        // printf("%s\n", tmp1);
        // for(char *it = tmp1;*it != '\0';it++){
        //     if(*it == '*') continue;
        //     else{
        //         func_arr[idx] = it;
        //         break;
        //     }
        // }
        remove_asterisks(tmp1); // 去除 * 字元
        func_arr[idx] = strdup(tmp1); // 複製處理後的字串到 func_arr
        idx++;
    }
    // for(int32_t i = 0;i < idx;i++){
    //     printf("%s\n", func_arr[i]);
    // }
    for(int32_t i = 0;i < idx;i++){
        while(!feof(pFile)){
            char buffer[500];
            fgets(buffer, 500, pFile);
            if(strstr(buffer, func_arr[i]) != NULL){
                cnt++;
            }
        }
        fseek(pFile, 0, SEEK_SET);
        printf("%s:\n", func_arr[i]);
        printf("  %s (count: %d)\n", filename, cnt);
        int32_t line_cnt = 0;
        while(!feof(pFile)){
            line_cnt++;
            char buffer[500];
            fgets(buffer, 500, pFile);
            buffer[strlen(buffer) - 1] = '\0';
            if(strstr(buffer, func_arr[i]) != NULL){
                if(line_flag || code_flag) printf("    ");
                if(line_flag)
                    printf("line %d:", line_cnt);
                if(code_flag)
                    printf("%s", buffer);
                if(line_flag || code_flag) printf("\n");
            }
        }
    }
    return 1;
}

void help(){
    printf("Usage: hw0302 [ options ] ... [files] ...\n");
    printf("  -f, --function =func Trace the func usage in [Files].\n");
    printf("  -i, --include =File Trace all functions listed in the header file in [Files].\n");
    printf("  -l, --linum Display the line number.\n");
    printf("  -c, --code Display the code.\n");
    printf("  -h, --help Display this information and exit.\n\n");
    printf("-f and -i are exclusive and must be at least one.\n");
}