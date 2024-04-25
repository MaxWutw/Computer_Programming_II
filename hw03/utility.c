#include "utility.h"

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
        fgets(buffer, 500, hFile);
        sscanf(buffer, "%*[^ ] %*[*]%[^(]", tmp1);
        if(tmp1[0] == '\n') continue;
        printf("%s\n", tmp1);
        idx++;
    }
    // for(int32_t i = 0;i < idx;i++){
    //     while(!feof(pFile)){
    //         char buffer[500];
    //         fgets(buffer, 500, pFile);
    //         if(strstr(buffer, func_arr[i]) != NULL){
    //             cnt++;
    //         }
    //     }
    //     fseek(pFile, 0, SEEK_SET);
    //     printf("%s:\n", func_arr[i]);
    //     printf("  %s (count: %d)\n", filename, cnt);
    //     int32_t line_cnt = 0;
    //     while(!feof(pFile)){
    //         line_cnt++;
    //         char buffer[500];
    //         fgets(buffer, 500, pFile);
    //         buffer[strlen(buffer) - 1] = '\0';
    //         if(strstr(buffer, func_arr[i]) != NULL){
    //             if(line_flag || code_flag) printf("    ");
    //             if(line_flag)
    //                 printf("line %d:", line_cnt);
    //             if(code_flag)
    //                 printf("%s", buffer);
    //             printf("\n");
    //         }
    //     }
    // }
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