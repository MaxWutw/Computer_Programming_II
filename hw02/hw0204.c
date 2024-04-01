#include <stdio.h>
#include <stdint.h>
#include <math.h>
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

typedef struct _sBmpHeader sBmpHeader;

void print_bmp_header( sBmpHeader *pHeader )
{
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


int main(){
    freopen("test.in", "r", stdin);
    char filename[50], outputname[50];
    FILE *pFile, *pDestination;
    float angle;
    fprintf(stdout, "Please input a BMP file: ");
    fscanf(stdin, "%s", filename);
    fprintf(stdout, "Please input the output BMP file name: ");
    fscanf(stdin, "%s", outputname);
    fprintf(stdout, "Angle (0 -90): ");
    fscanf(stdin, "%f", &angle);
    if((pFile = fopen(filename, "rb")) == NULL){
        fprintf(stderr, "Error: Unable to open file for reading and writing\n");
        return 0;
    }
    if((pDestination = fopen(outputname, "wb")) == NULL){
        fprintf(stderr, "Error: Unable to open file for reading and writing\n");
        return 0;
    }
    sBmpHeader header;
    fread(&header, sizeof(header), 1, pFile);
    int32_t side = (header.height / sin(angle)) * cos(angle);
    header.width += side;
    fwrite(&header, sizeof(header), 1, pDestination);
    int32_t row_size = ((header.bpp * header.width) / 32) * 4;  
    while(!feof(pFile)){
        uint8_t origin[999] = {0}, modified[999] = {0};
        size_t cnt = fread(origin, 1, 999, pFile);
        for(size_t i = 0;i < side;i++){
            modified[i] = 255;
        }
        for(int32_t i = side;i < row_size;i++) modified[i] = 0;
        side--;
        fwrite(modified, cnt, 1, pDestination);
    }
    print_bmp_header(&header);
    fclose(pFile);
    fclose(pDestination);

    return 0;
}