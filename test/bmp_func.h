#ifndef _BMP_FUNC_H_
#define _BMP_FUNC_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
struct _sBmpHeader{
    char bm[2];
    uint32_t size;
    uint32_t reserve;
    uint32_t offset;
    uint32_t header_size;
    int32_t width;
    int32_t height;
    uint16_t planes; // must be 1
    uint16_t bpp; // bits per pixel
    uint32_t compression;
    uint32_t bitmap_size;
    uint32_t horizontal_res;
    uint32_t vertical_res;
    uint32_t used;
    uint32_t important;
}__attribute__ ((__packed__));

struct _sPixel{
    uint8_t b;
    uint8_t g;
    uint8_t r;
}__attribute__ ((__packed__));

typedef struct _sBmpHeader sBmpHeader;
typedef struct _sPixel sPixel;

int32_t parseheader(FILE *pFile, sBmpHeader *);
int32_t readbmp(FILE *pFile, uint8_t *, sBmpHeader *);
int32_t writebmp(FILE *pDestination, uint8_t *pixel, sBmpHeader *header);
void print_bmp_header(sBmpHeader *);

#endif