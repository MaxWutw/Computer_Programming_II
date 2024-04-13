#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include "bmp_func.h"
int main(){
    char filename[50], outputname[50], newfile[50];
    FILE *pFile, *pDestination;
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
    if((pFile = fopen(newfile, "rb")) == NULL){
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