#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include "utility.h"
struct option long_options[] = {
    {"function", 1, NULL, 'f'},
    {"include", 1, NULL, 'i'},
    {"linum", 0, NULL, 'l'},
    {"code", 0, NULL, 'c'},
    {"help", 0, NULL, 'h'},
    {0, 0, 0, 0},
};

int main(int argc, char *argv[]){
    // printf("argc: %d\n", argc);
    
    // for(int32_t i = 0 ; i < argc ; i++){
    //     printf("argv[%d]: %s\n", i, argv[i]);
    // }

    int32_t c;
    char *headername, *function_name;
    int8_t only = 0;
    int8_t line_flag = 0, code_flag = 0, help_flag = 0, trace_flag = 0, func_flag = 0;
    while((c = getopt_long(argc, argv, "f:i:lch", long_options, NULL)) != -1){
        if(c == 'f'){
            if(only){
                fprintf(stderr, "Error: -f and -i are exclusive and must be at least one.\n");
                return 0;
            }
            only = 1;
            // printf("-f, %s\n", optarg);
            function_name = optarg;
            // printf("-f, %s\n", function_name);
            trace_flag = 1;
        }
        else if(c == 'i'){
            if(only){
                fprintf(stderr, "Error: -f and -i are exclusive and must be at least one.\n");
                return 0;
            }
            only = 1;
            // printf("-i, %s\n", optarg);
            headername = optarg;
            // printf("-i, %s\n", headername);
            func_flag = 1;
        }
        else if(c == 'l'){
            line_flag = 1;
        }
        else if(c == 'c'){
            code_flag = 1;
        }
        else if(c == 'h'){
            help_flag = 1;
        }
    }
    if(help_flag){
        help();
        return 0;
    }
    for(int32_t i = optind;i < argc;i++){
        char *filename = argv[i];
        if(trace_flag){
            trace(line_flag, code_flag, function_name, filename);
        }
        else if(func_flag){
            func(line_flag, code_flag, headername, filename);
        }
    }

    return 0;
}