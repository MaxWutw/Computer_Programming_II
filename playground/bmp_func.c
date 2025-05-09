#include "bmp_func.h"

int32_t parseheader(FILE *pFile, struct sBmpHeader *header){
    fread(header, sizeof(*header), 1, pFile);
}

int32_t readbmp(FILE *pFile, struct sPixel **pixel, struct sBmpHeader *header){
    int32_t padding_sz = (((24 * header->width + 31) / 32) * 4) - (3 * header-width);
    int8_t temp[4];
    for(int32_t i = 0;i < header->height;i++){
        for(int32_t j = 0;j < header->width;j++){
            fread((sPixel * i) + j, sizeof(struct _sPixel), 1, pFile);
        }
        fread(temp, padding_sz, 1, pFile);
    }
}

int32_t writebmp(){
    
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