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
    sPixel *pixel = (sPixel *)malloc(header.height * header.width * sizeof(sPixel));
    readbmp(pFile, pixel, &header);
    fwrite(&header, sizeof(header), 1, pDestination);
    for(int32_t i = 0;i < header.height;i++){
        int32_t idx = 0;
        uint8_t modified[header.width * sizeof(sPixel)];
        for(int32_t j = 0;j < header.width * 3;j+=3){
            // printf("%u\n", (pixel + (i * header.height) + j)->b);
            modified[idx++] = (pixel + (i * header.height) + j)->b;
            modified[idx++] = (pixel + (i * header.height) + j)->g;
            modified[idx++] = (pixel + (i * header.height) + j)->r;
        }
        fwrite(modified, idx, 1, pDestination);
    }
    fclose(pFile);
    fclose(pDestination);

    return 0;
}