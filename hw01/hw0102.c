#include <stdio.h>
#include <stdlib.h>
#include "mycal.h"
int main(){
    char *str;
    char *data = "ABC_16 + 00010_2 * 13_10 * ABC_16";
    // calculate(data, 10, &str);
    // char *num = "01011_2";
    // printf("%d\n", convert2base10(data));
    calculate(data, 16, &str);

    return 0;
}