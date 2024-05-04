#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
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
    printf("%s\n", newfile);
    if((pFile = fopen(filename, "r+b")) == NULL){
        fprintf(stderr, "Error: Unable to open file for reading or writing\n");
        return 0;
    }
    if((pBinary = fopen(newfile, "r+")) == NULL){
        fprintf(stderr, "Error: Unable to open file for reading or writing\n");
        return 0;
    }
    if(strcmp(filename, "des.bmp") != 0){
        if((pDestination = fopen("des.bmp", "wb")) == NULL){
            fprintf(stderr, "Error: Unable to open file for reading or writing\n");
            return 0;
        }
    }
    // OPEN end

    // READ data
    sBmpHeader header;
    parseheader(pFile, &header);
    uint8_t *pixel = (uint8_t *)malloc(header.height * header.width * sizeof(uint8_t) * 3);
    readbmp(pFile, pixel, &header);
    // READ data end

    // PROCESS
    if(wr){
        fseek(pBinary, 0, SEEK_END);
        int32_t binary_byte = ftell(pBinary);
        printf("%d\n", binary_byte);
        printf("%d\n", bit);
        if((binary_byte * 8) > (header.width * header.height * 3 * bit)){
            fprintf(stderr, "Error: The secret data is larger than cover_bmp!\n");
            return 0;
        }
        header.reserve = binary_byte;
        fseek(pBinary, 0, SEEK_SET);
        uint8_t *newPixels = (uint8_t *)malloc(header.height * header.width * sizeof(uint8_t) * 3);
        uint8_t mem = 0;
        int32_t idx = 0, remain = 0, shift = bit;
        fread(&mem, 1, 1, pBinary);
        int32_t row = 0, col = 0;
        while(!feof(pBinary)){
            fread(&mem, 1, 1, pBinary);
            if(row > (header.width * 3)){
                row = 0;
                col++;
            }
            idx += bit;
            if(idx > 8){
                remain = (idx - 8);
                idx = 8;
                shift = bit - remain;
            }
            uint8_t mask = (1 << shift) - 1, start = (8 - idx);
            uint8_t mask2 = (mask << start);
            uint8_t tmp = ((mem & mask2) >> (8 - idx));
            *(pixel + (col * header.width * 3) + row) &= ~mask;
            *(newPixels + (col * header.width * 3) + row) = (*(pixel + (col * header.width * 3) + row) | tmp);
            if(remain != 0){
                // printf("remain\n");
                row++;
                fread(&mem, 1, 1, pBinary);
                idx = remain;
                shift = bit;
                mask = (1 << remain) - 1, start = (8 - idx);
                mask2 = (mask << start);
                tmp = ((mem & mask2) >> (8 - idx));
                remain = 0;
                *(pixel + (col * header.width * 3) + row) &= ~mask;
                *(newPixels + (col * header.width * 3) + row) = (*(pixel + (col * header.width * 3) + row) | tmp);
            }
            else if(idx == 8){
                // printf("idx\n");
                row++;
                fread(&mem, 1, 1, pBinary);
            }
        }
        printf("col: %d, row: %d\n", col, row);
        int8_t judge = 1;
        for(int32_t i = col;i < header.height;i++){
            for(int32_t j = (judge ? row : 0);j < header.width * 3;j++){
                judge = 0;
                *(newPixels + (i * header.width * 3) + j) = (*(pixel + (i * header.width * 3) + j));
            }
        }
        fwrite(&header, sizeof(header), 1, pDestination);
        writebmp(pDestination, newPixels, &header);
    }
    // else if(ex){
    //     // fwrite(&header, sizeof(header), 1, pBinary);
    //     uint8_t mem = 0;
    //     int32_t idx = 0, remain = 0, shift = bit;
    //     for(int32_t i = 0;i < header.height;i++){
    //         for(int32_t j = 0;j < header.width;j++){
    //             for(int32_t k = 0;k < 3;k++){
    //                 idx += bit;
    //                 if(idx > 8){
    //                     remain = (idx - 8);
    //                     idx = 8;
    //                     shift = bit - remain;
    //                 }
    //                 int8_t mask = (1 << shift) - 1;
    //                 if(k == 0){
    //                     int8_t get_last = (pixel + i * header.width + j)->b & mask;
    //                     get_last <<= (8 - idx);
    //                     mem |= get_last;
    //                 }
    //                 else if(k == 1){
    //                     int8_t get_last = (pixel + i * header.width + j)->g & mask;
    //                     get_last <<= (8 - idx);
    //                     mem |= get_last;
    //                 }
    //                 else if(k == 2){
    //                     int8_t get_last = (pixel + i * header.width + j)->r & mask;
    //                     get_last <<= (8 - idx);
    //                     mem |= get_last;
    //                 }
    //                 if(idx == 8){
    //                     idx = 0;
    //                     fwrite(&mem, 1, 1, pBinary);
    //                 }
    //                 if(remain != 0){
    //                     mem = 0;
    //                     idx = remain;
    //                     mask = ((1 << remain) - 1) << (bit - remain);
    //                     if(k == 0){
    //                         int8_t get_last = (pixel + i * header.width + j)->b & mask;
    //                         get_last >>= (bit-remain);
    //                         get_last <<= (8 - idx);
    //                         mem |= get_last;
    //                     }
    //                     else if(k == 1){
    //                         int8_t get_last = (pixel + i * header.width + j)->g & mask;
    //                         get_last >>= (bit-remain);
    //                         get_last <<= (8 - idx);
    //                         mem |= get_last;
    //                     }
    //                     else if(k == 2){
    //                         int8_t get_last = (pixel + i * header.width + j)->r & mask;
    //                         get_last >>= (bit-remain);
    //                         get_last <<= (8 - idx);
    //                         mem |= get_last;
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }
    // int8_t data = 4;
    // int8_t rda = 0;
    // fread(&rda, 1, 1, pBinary);
    // fwrite(&data, 1, 1, pBinary);
    // printf("%u\n", rda);
    // PROCESS end

    // CLOSE
    fclose(pFile);
    fclose(pBinary);
    fclose(pDestination);
    // FINISH

    return 0;
}