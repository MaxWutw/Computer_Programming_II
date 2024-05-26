// #include <stdio.h>
// #include <stdlib.h>

// int main(){
//     int32_t number = 0;
//     scanf("%d", &number);
//     int32_t bit = 1;
//     bit = bit << 31;
//     printf("%d\n", bit);
//     for(int i = 0;i < 32;i++){
//         if(bit & number){
//             printf("1");
//             printf("if: %d %d\n", bit & number, i);
//         }
//         else{
//             printf("else: %d %d\n", bit, i);
//             // printf("0");
//         }
//         bit = bit >> 1;
//     }

//     return 0;
// }

#include <stdio.h>
#include <stdint.h>

int main(){
    int32_t number = 0;
    scanf("%d", &number);
    uint32_t bit = 1 << 31;  // 使用無號整數來進行位操作，防止負數位移錯誤
    for(int i = 0; i < 32; i++){
        if(bit & number)
            printf("1");
        else 
            printf("0");
        bit = bit >> 1;
    }
    printf("\n");  // 在輸出結束後換行
    return 0;
}
