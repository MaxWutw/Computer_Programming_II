#include <stdio.h>
#include <stdint.h>

#define ROWS 3
#define COLS 3

int main() {
    int8_t a = 47;
    uint8_t base = 0x03;
    printf("%d\n", (a >> 6) & base);
    
    return 0;
}