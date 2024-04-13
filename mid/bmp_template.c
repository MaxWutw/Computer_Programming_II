#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include "bmp_func.h"
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
    int32_t origin_height = header.height, origin_width = header.width;
    sPixel *pixel = (sPixel *)malloc(header.height * header.width * sizeof(sPixel));
    readbmp(pFile, pixel, &header);
    // READ data end

    // PROCESS
    sPixel *newPixels = (sPixel *)malloc(header.height * header.width * sizeof(sPixel));
    fwrite(&header, sizeof(header), 1, pDestination);
    for(int32_t i = 0;i < header.height;i++){
        for(int32_t j = 0;j < header.width;j++){
            *(newPixels + i * header.width + j) = *(pixel + i * header.width + j);
        }
    }
    writebmp(pDestination, newPixels, &header);
    // PROCESS end

    // CLOSE
    fclose(pFile);
    fclose(pDestination);
    // FINISH

    return 0;
}