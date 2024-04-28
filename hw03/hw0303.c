#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include "bmp_func.h"
struct option long_options[] = {
    {"write", 0, NULL, 'w'},
    {"extract", 0, NULL, 'e'},
    {"bits", 1, NULL, 'b'},
    {0, 0, 0, 0},
};
int32_t str2int(char *str){
    int32_t ret = 0;
    for(const char *it = str;*it != 0;it++){
        ret = (*it - '0') + (ret * 10);
    }
    return ret;
}
int main(int argc, char *argv[]){
    FILE *pFile, *pBinary;

    int32_t c;
    int8_t wr = 0, ex = 0, bit = 1;
    while((c = getopt_long(argc, argv, "web:", long_options, NULL)) != -1){
        if(c == 'w'){
            if(ex){
                fprintf(stderr, "Error: -w and -e are exclusive!\n");
                return 0;
            }
            wr = 1;
        }
        else if(c == 'e'){
            if(wr){
                fprintf(stderr, "Error: -w and -e are exclusive!\n");
                return 0;
            }
            ex = 1;
        }
        else if(c == 'b'){
            // printf("%s\n", optarg);
            bit = str2int(optarg);
        }
    }
    if(!ex && !wr){
        fprintf(stderr, "Error: You need to select at least on option!\n");
        return 0;
    }
    // OPEN file
    char *filename = argv[optind];
    char *newfile = argv[optind + 1];
    FILE *pDestination;
    printf("%s\n", filename);
    if((pFile = fopen(filename, "r+b")) == NULL){
        fprintf(stderr, "Error: Unable to open file for reading or writing\n");
        return 0;
    }
    if((pBinary = fopen(newfile, "r+b")) == NULL){
        fprintf(stderr, "Error: Unable to open file for reading or writing\n");
        return 0;
    }
    if((pDestination = fopen("des.bmp", "wb")) == NULL){
        fprintf(stderr, "Error: Unable to open file for reading or writing\n");
        return 0;
    }
    // OPEN end

    // READ data
    sBmpHeader header;
    parseheader(pFile, &header);
    sPixel *pixel = (sPixel *)malloc(header.height * header.width * sizeof(sPixel));
    readbmp(pFile, pixel, &header);
    // READ data end

    // PROCESS
    if(wr){
        fseek(pBinary, 0, SEEK_END);
        int32_t binary_byte = ftell(pBinary);
        // printf("%d\n", binary_byte);
        // printf("%d\n", bit);
        if((binary_byte * 8) > (header.width * header.height * 3 * bit)){
            fprintf(stderr, "Error: The secret data is larger than cover_bmp!\n");
            return 0;
        }
        header.reserve = binary_byte;
        fseek(pBinary, 0, SEEK_SET);
        sPixel *newPixels = (sPixel *)malloc(header.height * header.width * sizeof(sPixel));
        uint8_t mem = 0;
        int32_t idx = 0, remain = 0, shift = bit;
        fread(&mem, 1, 1, pBinary);
        for(int32_t i = 0;i < header.height;i++){
            for(int32_t j = 0;j < header.width;j++){
                for(int32_t k = 0;k < 3;k++){
                    idx += bit;
                    if(idx > 8){
                        remain = (idx - 8);
                        idx = 8;
                        shift = bit - remain;
                    }
                    int8_t mask = (1 << shift) - 1, start = (8 - idx);
                    int8_t mask2 = (mask << start);
                    int8_t tmp = ((mem & mask2) >> (8 - idx));
                    if(k == 0){
                        (pixel + i * header.width + j)->b &= ~mask;
                        (newPixels + i * header.width + j)->b = ((pixel + i * header.width + j)->b | tmp);
                    }
                    else if(k == 1){
                        (pixel + i * header.width + j)->g &= ~mask;
                        (newPixels + i * header.width + j)->g = ((pixel + i * header.width + j)->g | tmp);
                    }
                    else if(k == 2){
                        (pixel + i * header.width + j)->r &= ~mask;
                        (newPixels + i * header.width + j)->r = ((pixel + i * header.width + j)->r | tmp);
                    }
                    if(remain != 0){
                        fread(&mem, 1, 1, pBinary);
                        idx = remain;
                        shift = bit;
                        mask = (1 << remain) - 1, start = (8 - idx);
                        mask2 = (mask << start);
                        tmp = ((mem & mask2) >> (8 - idx));
                        remain = 0;
                        if(k == 0){
                            (pixel + i * header.width + j)->b &= ~mask;
                            (newPixels + i * header.width + j)->b = ((pixel + i * header.width + j)->b | tmp);
                        }
                        else if(k == 1){
                            (pixel + i * header.width + j)->g &= ~mask;
                            (newPixels + i * header.width + j)->g = ((pixel + i * header.width + j)->g | tmp);
                        }
                        else if(k == 2){
                            (pixel + i * header.width + j)->r &= ~mask;
                            (newPixels + i * header.width + j)->r = ((pixel + i * header.width + j)->r | tmp);
                        }
                    }
                    else if(idx == 8){
                        fread(&mem, 1, 1, pBinary);
                    }
                }
            }
        }
        fwrite(&header, sizeof(header), 1, pDestination);
        writebmp(pDestination, newPixels, &header);
    }
    else if(ex){
        fwrite(&header, sizeof(header), 1, pBinary);
        for(int32_t i = 0;i < header.height;i++){
            for(int32_t j = 0;j < header.width;j++){
                for(int32_t k = 0;k < 3;k++){
                    fwrite()
                }
            }
        }
    }
    
    // PROCESS end

    // CLOSE
    fclose(pFile);
    fclose(pBinary);
    fclose(pDestination);
    // FINISH

    return 0;
}