#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "mycal.h"

int main(){
    uint8_t tmp = 202;
    uint8_t base = 0x03;
    // printf("%d\n", tmp & base);
    for(int32_t i = 3;i >= 0;i--){
        printf("%d\n", (tmp >> (i << 1) & base));
    }
    
    return 0;
}
