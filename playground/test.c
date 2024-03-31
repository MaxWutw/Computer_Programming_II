#include <stdio.h>
#include <string.h>
#include <stdint.h>
int32_t digit(int32_t num){
    int32_t ret = 0;
    while(num){
        num /= 10;
        ret++;
    }
    return ret;
}
int main() {
    int32_t readed = 1;
    printf("%d\n", digit(readed));

    return 0;
}
