#include <stdio.h>
#include <stdint.h>
#include "mycal.h"

int main(){
    char input[100] = "BEEF_16 * A12_12";
    int32_t base = 16;
    char *pResult = NULL;
    int32_t RETURN = calculate(input, base, &pResult);
    //printf("%d\n", RETURN);
    printf("%s\n", pResult);
}
