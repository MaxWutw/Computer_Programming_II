#include <stdio.h>
#include <stdlib.h>
#include "mymaze.h"
int main(){
    sRoom pMaze[15];
    sPath pMinPath;
    pMinPath.pPath = NULL;
    uint8_t row = 3, col = 4;
    pMaze[0 * col + 0].cost = 1;
    pMaze[0 * col + 0].doors = (uint8_t)0b01110101;

    pMaze[0 * col + 1].cost = 7;
    pMaze[0 * col + 1].doors = (uint8_t)0b11000011;

    pMaze[0 * col + 2].cost = 2;
    pMaze[0 * col + 2].doors = (uint8_t)0b11011100;

    pMaze[0 * col + 3].cost = 8;
    pMaze[0 * col + 3].doors = (uint8_t)0b11100101;

    pMaze[1 * col + 0].cost = 2;
    pMaze[1 * col + 0].doors = (uint8_t)0b00101111;

    pMaze[1 * col + 1].cost = 5;
    pMaze[1 * col + 1].doors = (uint8_t)0b10111100;

    pMaze[1 * col + 2].cost = 10;
    pMaze[1 * col + 2].doors = (uint8_t)0b01001010;

    pMaze[1 * col + 3].cost = 2;
    pMaze[1 * col + 3].doors = (uint8_t)0b01111001;

    pMaze[2 * col + 0].cost = 9;
    pMaze[2 * col + 0].doors = (uint8_t)0b00101100;

    pMaze[2 * col + 1].cost = 15;
    pMaze[2 * col + 1].doors = (uint8_t)0b01111011;

    pMaze[2 * col + 2].cost = 7;
    pMaze[2 * col + 2].doors = (uint8_t)0b01111010;

    pMaze[2 * col + 3].cost = 3;
    pMaze[2 * col + 3].doors = (uint8_t)0b10001101;

    
    // printf("%d\n", pMaze[0].doors);
    find_min_path(pMaze, row, col, &pMinPath);
    free(pMinPath.pPath);

    return 0;
}