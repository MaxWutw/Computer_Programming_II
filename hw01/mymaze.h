#ifndef _MYMAZE_H_
#define _MYMAZE_H_
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct _sRoom {
    uint32_t cost; 
    uint8_t doors;  // 8 bits: aabbccdd
                    // aa: the up door number 0-3
                    // bb: the right door number 0-3 // cc: the down number 0-3
                    // dd: the left door number 0-3

} sRoom;

typedef struct _sPoint {
    uint32_t row;
    uint32_t col;
} sPoint;

typedef struct _sPath {
    uint32_t length; // Path length. uint32_t cost; // Cost
    sPoint *pPath; // An array of all points in order. 
} sPath;
// The start point is pMaze[0][0] and the exit point is pMaze[row-1][col-1]
// If there is no path, return 0; If there is any errors in inputs, return -1;otherwise, return 1;

int32_t find_min_path( const sRoom *pMaze, const uint8_t row, const uint8_t col, sPath *pMinPath );


#endif