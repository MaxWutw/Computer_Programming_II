#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "bmp_func.h"


int main(){
    freopen("test.in", "r", stdin);
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
    parseheader(pFile, &header);
    angle = 90.0 - angle;
    double radian = angle * M_PI / 180.0;
    int32_t side = (header.height / sin(radian)) * cos(radian), reverse = 0;
    // int32_t side = header.height * (1 / tan(angle)), reverse = 0;
    // printf("%d\n", side);
    // print_bmp_header(&header);
    // printf("\n");
    sPixel *pixel = (sPixel *)malloc(header.height * header.width * sizeof(sPixel));
    
    readbmp(pFile, pixel, &header);
    // for(int32_t i = 0;i < header.height;i++){
    //     for(int32_t j = 0;j < header.width;j++){
    //         printf("%d ", (pixel + (i * header.height) + j)->b);
    //         printf("%d ", (pixel + (i * header.height) + j)->g);
    //         printf("%d ", (pixel + (i * header.height) + j)->r);
    //     }
    //     printf("\n");
    // }
    // fwrite(&header, sizeof(header), 1, pDestination);
    // for(int32_t i = 0;i < header.height;i++){
    //     for(int32_t j = 0;j < header.width;j++){
    //         size_t cnt = fwrite(pixel + (i * header.width) + j, 1, sizeof(sPixel), pDestination);
    //         // printf("%lld\n", cnt);
    //         // printf("s");
    //     }
    //     // for (int32_t k = 0; k < ((4 - ((header.width * 3) % 4)) % 4); k++) {
    //     //     fputc(0, pDestination);
    //     // }
    // }
    int32_t origin_width = header.width;
    int32_t padding_sz = (((header.bpp * header.width + 31) / 32) * 4) - (3 * header.width);
    header.width += side;
    header.bitmap_size = header.width * header.height * (header.bpp / 4);
    header.size = 54 + header.bitmap_size;
    int32_t padding = side, color = (header.bpp / 8);
    side *= color;
    fwrite(&header, sizeof(header), 1, pDestination);
    int32_t oppo = 0;
    if(header.height < 0) oppo = 1;
    float remain = 0.0;
    for(int32_t i = 0;i < header.height;i++){
        int32_t idx = 0;
        uint8_t modified[padding * 2 + origin_width * color + 10000];
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
        for(int32_t j = 0;j < origin_width;j++){
            modified[idx++] = (pixel + (i * origin_width) + j)->b;
            modified[idx++] = (pixel + (i * origin_width) + j)->g;
            modified[idx++] = (pixel + (i * origin_width) + j)->r;
            // idx++;
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
        while(tmp >= 1.0){
            remain += 1.0;
            tmp -= 1.0;
        }
        if(tmp < 1.0){
            remain += tmp;
        }
        while(remain >= 1.0){
            reverse += color;
            side -= color;
            remain -= 1.0;
        }
    }
    fclose(pFile);
    fclose(pDestination);

    return 0;
}