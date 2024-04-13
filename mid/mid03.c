#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include "bmp_func.h"

void resizeBmpLinearly(sPixel *original_pixel, sBmpHeader *original_header, sPixel *resized_pixel, sBmpHeader *resized_header, int new_width, int new_height){
    float width_ratio = (float)original_header->width / (float)new_width;
    float height_ratio = (float)original_header->height / (float)new_height;

    for(int32_t i = 0; i < new_height; i++){
        for(int32_t j = 0; j < new_width; j++){
            int32_t original_x = (int32_t)(j * width_ratio);
            int32_t original_y = (int32_t)(i * height_ratio);

            resized_pixel[i * new_width + j] = original_pixel[original_y * original_header->width + original_x];
        }
    }

    // Update resized BMP header
    resized_header->width = new_width;
    resized_header->height = new_height;
    resized_header->bitmap_size = new_width * new_height * sizeof(sPixel);
    resized_header->reserve = resized_header->offset + resized_header->bitmap_size;
}
int main(){
    // freopen("test.in", "r", stdin);
    char filename[50], outputname[50], newfile[50];
    FILE *pFile, *pNew, *pDestination;
    // OPEN file
    int32_t x, y, w, h;
    fprintf(stdout, "cover: ");
    fscanf(stdin, "%s", filename);
    fprintf(stdout, "x (in pixel): ");
    fscanf(stdin, "%d", &x);
    fprintf(stdout, "y (in pixel): ");
    fscanf(stdin, "%d", &y);
    fprintf(stdout, "w (in pixel): ");
    fscanf(stdin, "%d", &w);
    fprintf(stdout, "h (in pixel): ");
    fscanf(stdin, "%d", &h);

    fprintf(stdout, "new: ");
    fscanf(stdin, "%s", newfile);
    fprintf(stdout, "output: ");
    fscanf(stdin, "%s", outputname);

    if((pFile = fopen(filename, "rb")) == NULL){
        fprintf(stderr, "Error: Unable to open file for reading and writing\n");
        return 0;
    }
    if((pNew = fopen(newfile, "rb")) == NULL){
        fprintf(stderr, "Error: Unable to open file for reading and writing\n");
        return 0;
    }
    if((pDestination = fopen(outputname, "wb")) == NULL){
        fprintf(stderr, "Error: Unable to open file for reading and writing\n");
        return 0;
    }
    // FILE *pSmall;
    // if((pSmall = fopen("small.bmp", "wb")) == NULL){
    //     fprintf(stderr, "Error: Unable to open file for reading and writing\n");
    //     return 0;
    // }
    // OPEN end

    // READ data
    sBmpHeader cover_header, new_header, resized_header;
    parseheader(pFile, &cover_header);
    parseheader(pNew, &new_header);
    sPixel *cover_pixel = (sPixel *)malloc(cover_header.height * cover_header.width * sizeof(sPixel));
    readbmp(pFile, cover_pixel, &cover_header);
    sPixel *new_pixel = (sPixel *)malloc(new_header.height * new_header.width * sizeof(sPixel));
    readbmp(pNew, new_pixel, &new_header);
    // READ data end
    // PROCESS
    sPixel *resized_pixel = (sPixel *)malloc(w * h * sizeof(sPixel));
    resizeBmpLinearly(new_pixel, &new_header, resized_pixel, &new_header, w, h);
    // fwrite(&new_header, sizeof(new_header), 1, pSmall);
    // writebmp(pDestination, newPixels, &cover_header);
    fwrite(&cover_header, sizeof(cover_header), 1, pDestination);
    // printf("%d %d\n", new_header.height, new_header.width);

    for(int32_t i = 0;i < new_header.height;i++){
        for(int32_t j = 0;j < new_header.width;j++){
            // sPixel black = {0, 0, 0}; // 黑色
            *(cover_pixel + ((i + cover_header.height - y - new_header.height) * cover_header.width) + j + x) = *(resized_pixel + (i * new_header.width) + j);
        }
    }


    // printf("%d %d\n", resized_header.height, resized_header.width);
    // writebmp(pSmall, resized_pixel, &new_header);
    writebmp(pDestination, cover_pixel, &cover_header);
    // PROCESS end

    // CLOSE
    fclose(pFile);
    fclose(pNew);
    fclose(pDestination);
    // FINISH

    return 0;
}