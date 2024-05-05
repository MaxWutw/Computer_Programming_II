#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include "bmp_func.h"
void resizeBmpLinearly(sPixel *original_pixel, sBmpHeader *original_header, sPixel *resized_pixel, sBmpHeader *resized_header, int new_width, int new_height) {
    float width_ratio = (float)original_header->width / new_width;
    float height_ratio = (float)original_header->height / new_height;

    for (int i = 0; i < new_height; i++) {
        for (int j = 0; j < new_width; j++) {
            int original_x = width_ratio * j;
            int original_y = height_ratio * i;

            int index_original = original_y * original_header->width + original_x;
            sPixel pixel = original_pixel[index_original];

            int index_resized = i * new_width + j;
            resized_pixel[index_resized] = pixel;
        }
    }

    // 更新新圖片的標頭
    resized_header->width = new_width;
    resized_header->height = new_height;
}
int main(){
    char filename[50], outputname[50];
    FILE *pFile, *pDestination;
    // OPEN file
    fprintf(stdout, "Please input a BMP file: ");
    fscanf(stdin, "%s", filename);
    fprintf(stdout, "Please input the output BMP file name: ");
    fscanf(stdin, "%s", outputname);

    if((pFile = fopen(filename, "rb")) == NULL){
        fprintf(stderr, "Error: Unable to open file for reading and writing\n");
        return 0;
    }
    if((pDestination = fopen(outputname, "wb")) == NULL){
        fprintf(stderr, "Error: Unable to open file for reading and writing\n");
        return 0;
    }
    // OPEN end

    // READ data
    sBmpHeader header;
    parseheader(pFile, &header);
    // int32_t origin_height = header.height, origin_width = header.width;
    sPixel *pixel = (sPixel *)malloc(header.height * header.width * sizeof(sPixel));
    readbmp(pFile, pixel, &header);
    // READ data end

    // PROCESS
    int new_width = header.width / 2; // 替換為你想要的新寬度
    int new_height = header.height / 2; // 替換為你想要的新高度
    sPixel *rotatedPixels = (sPixel *)malloc(header.height * header.width * sizeof(sPixel));
    sPixel *resized_pixel = (sPixel *)malloc(new_width * new_height * sizeof(sPixel));
    sBmpHeader resized_header;

    // 等比例縮小原始圖片
    resizeBmpLinearly(pixel, &header, resized_pixel, &resized_header, new_width, new_height);
    fwrite(&header, sizeof(header), 1, pDestination);
    // 寫入縮小後的圖片到檔案
    writebmp(pDestination, resized_pixel, &resized_header);
    // PROCESS end

    // CLOSE
    fclose(pFile);
    fclose(pDestination);
    // FINISH

    return 0;
}