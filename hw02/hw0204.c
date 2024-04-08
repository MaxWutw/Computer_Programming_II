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
    char filename[50], outputname[50];
    FILE *pFile, *pDestination;
    float angle;
    fprintf(stdout, "Please input a BMP file: ");
    fscanf(stdin, "%s", filename);
    fprintf(stdout, "Please input the output BMP file name: ");
    fscanf(stdin, "%s", outputname);
    fprintf(stdout, "Angle (0-90): ");
    fscanf(stdin, "%f", &angle);
    if(angle >= 90 || angle < 0){
        fprintf(stdout, "Error: The input should bewteen 0 and 90.\n");
        return 0;
    }
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
    angle = 90.0 - angle;
    double radian = angle * M_PI / 180.0;
    int32_t side = (header.height / sin(radian)) * cos(radian), reverse = 0;
    // int32_t side = header.height * (1 / tan(angle)), reverse = 0;
    // printf("%d\n", side);
    int32_t origin_width = header.width;
    header.width += side;
    header.bitmap_size = header.width * header.height * (header.bpp / 4);
    header.size = 54 + header.bitmap_size;
    int32_t padding = side, color = (header.bpp / 8);
    side *= color;
    fwrite(&header, sizeof(header), 1, pDestination);
    int32_t oppo = 0;
    if(header.height < 0) oppo = 1;
    float remain = 0.0;
    while(!feof(pFile)){
        uint8_t origin[999 * 10] = {0}, modified[999 * 10] = {0};
        size_t cnt = fread(origin, 1, origin_width * color, pFile);
        int32_t idx = 0;
        // printf("reverse: %d\n", reverse);
        if(!oppo){
            for(size_t i = 0;i < reverse;i++){
                modified[idx] = 255;
                idx++;
            }
        }
        else{
            for(size_t i = 0;i < side;i++){
                modified[idx] = 255;
                idx++;
            }
        }
        for(int32_t i = 0;i < cnt;i++){
            modified[idx] = origin[i];
            idx++;
        }
        if(!oppo){
            for(size_t i = 0;i < side;i++){
                modified[idx] = 255;
                idx++;
            }
        }
        else{
            for(size_t i = 0;i < reverse;i++){
                modified[idx] = 255;
                idx++;
            }
        }
        for(int32_t i = 0;i < ((4 - ((header.width * color) % 4)) % 4);i++){
            modified[idx] = 0;
            idx++;
        }
        fwrite(modified, idx, 1, pDestination);
        float tmp = (float)padding / (float)header.height;
        if(tmp < 0) tmp = -tmp;
        // printf("remain: %f\n", remain);
        if(tmp >= 1.0){
            remain += (tmp - 1);
            reverse += color;
            side -= color;
        }
        else if(tmp < 1.0){
            remain += tmp;
        }
        // printf("fdsfsads\n");
        if(remain > 1.0){
            // printf("fdsafsadf\n");
            reverse += color;
            side -= color;
            remain -= 1.0;
        }
    }
    // print_bmp_header(&header);
    fclose(pFile);
    fclose(pDestination);

    return 0;
}