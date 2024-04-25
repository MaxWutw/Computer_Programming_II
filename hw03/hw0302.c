#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
struct option long_options[] = {
    {"function", 1, NULL, 'f'},
    {"include", 1, NULL, 'i'},
    {"linum", 0, NULL, 'l'},
    {"code", 0, NULL, 'c'},
    {"help", 0, NULL, 'h'},
    {0, 0, 0, 0},
};

int main(int argc, int *argv[]){
    int32_t c;
    while(c = getopt_long(argc, argv, "f:i:lch", long_options, NULL) != -1){
        if(c == 'f'){

        }
        else if(c == 'i'){

        }
        else if(c == 'l'){

        }
        else if(c == 'c'){

        }
        else if(c == 'h'){

        }
    }

    return 0;
}