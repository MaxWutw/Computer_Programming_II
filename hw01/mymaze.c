#include "mymaze.h"

int32_t find_min_path( const sRoom *pMaze, const uint8_t row, const uint8_t col, sPath *pMinPath ){
    uint8_t tmp = 202;
    uint8_t base = 0x03;
    for(int32_t i = 3;i >= 0;i--){
        printf("%d\n", (tmp >> (i << 1) & base));
    }
    for(int32_t i = 0;i < row;i++){
        for(int32_t j = 0;j < col;j++){
            
        }
    }
}