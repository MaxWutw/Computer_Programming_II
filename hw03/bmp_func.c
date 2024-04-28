#include "bmp_func.h"

int32_t parseheader(FILE *pFile, sBmpHeader *header){
    fread(header, sizeof(*header), 1, pFile);
}

int32_t readbmp(FILE *pFile, sPixel *pixel, sBmpHeader *header){
    int32_t padding_sz = (((24 * header->width + 31) / 32) * 4) - (3 * header->width);
    int8_t temp[4];
    for(int32_t i = 0;i < header->height;i++){
        for(int32_t j = 0;j < header->width;j++){
            fread(pixel + (i * header->width) + j, sizeof(sPixel), 1, pFile);
        }
        fread(temp, padding_sz, 1, pFile);
    }
}

int32_t writebmp(FILE *pDestination, sPixel *pixel, sBmpHeader *header){
    // printf("%d %d\n", header->height, header->width);
    int32_t color = (header->bpp / 8);
    for(int32_t i = 0;i < header->height;i++){
        for(int32_t j = 0;j < header->width;j++){
            // printf("%u ",(pixel + (i * header->width + j))->r);
            fwrite(pixel + (i * header->width + j), sizeof(sPixel), 1, pDestination);
        }
        for(int32_t k = 0;k < ((4 - ((header->width * color) % 4)) % 4);k++)
            fputc(0, pDestination);
    }
}

void print_bmp_header(sBmpHeader *pHeader){
    printf( "ID: %c%c\n", pHeader -> bm[0], pHeader -> bm[1] );
    printf( "Size: %u\n", pHeader -> size );
    printf( "Reserve: %u\n", pHeader -> reserve );
    printf( "Offset: %u\n", pHeader -> offset );
    printf( "Header Size: %u\n", pHeader -> header_size );
    printf( "Width: %u\n", pHeader -> width );
    printf( "Height: %u\n", pHeader -> height );
    printf( "Planes: %u\n", pHeader -> planes );
    printf( "Bits Per Pixel: %u\n", pHeader -> bpp );
    printf( "Compression: %u\n", pHeader -> compression );
    printf( "Bitmap Data Size: %u\n", pHeader -> bitmap_size );
    printf( "H-Resolution: %u\n", pHeader -> horizontal_res );
    printf( "V-Resolution: %u\n", pHeader -> vertical_res );
    printf( "Used Colors: %u\n", pHeader -> used );
    printf( "Important Colors: %u\n", pHeader -> important );
    
    return;
}