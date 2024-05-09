#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>
#include <unistd.h>
#include "util.h"
#define GAME_SIZE (16 * 1024 * 1024)
#pragma pack(push, 1)
typedef struct _sPerson{
    uint8_t x;
    uint8_t y;
    uint8_t data[5];
    uint8_t cid;
    uint16_t name;
    uint8_t item[16];
    uint8_t others[29];
    uint16_t mt;
    uint16_t df;
    uint8_t mv;
    uint8_t ex;
    uint8_t tmp;
    uint16_t dx;
    uint16_t hp; // h1
    uint16_t hpmax; // h2
    uint16_t mp; // m1
    uint16_t mpmax; // m2
    uint8_t none[8];
}sPerson;
#pragma pack(pop)

uint64_t getFDsize(int fd){
    struct stat statbuf;
    if(fstat(fd, &statbuf) < 0){
        close(fd);
        return -1;
    }
    return statbuf.st_size;
}

void print_person(sPerson *per){
    printf("x: %hhu, y: %hhu\n", per->x, per->y);
    printf("HP: %hu, MAXHP: %hu\n", per->hp, per->hpmax);
    printf("MP: %hu, MAXMP: %hu\n", per->mp, per->mpmax);
    printf("name: %hu\n", per->name);
    printf("MT: %hu, DF: %hu, MV: %hhu, EX: %hhu, DX: %hu\n", per->mt, per->df, per->mv, per->ex, per->dx);
}

int main(int argc, char *argv[]){
    if(argc != 3){
        fprintf(stderr, "Usage: sudo ./hw0304 PID ADDR\n");
        return 0;
    }
    int32_t fd = 0;
    int32_t pid = strtol(argv[1], NULL, 10);
    char filename[50] = {0};
    uint64_t addr_start = strtoul(argv[2], NULL, 16);
    uint64_t addr_base = 0;

    snprintf(filename, 50, "/proc/%d/mem", pid);
    fd = open(filename, O_RDWR);
    if(fd == -1){
        fprintf(stderr, "ERROR: Failed to open the file\n");
        return 0;
    }
    uint8_t *pData = malloc(GAME_SIZE);
    uint16_t hp, hpmax;
    lseek(fd, addr_start, SEEK_SET);
    read(fd, pData, GAME_SIZE);
    fprintf(stdout, "Please enter your current HP: ");
    fscanf(stdin, "%d", &hp);
    fprintf(stdout, "Please enter your HP maximum: ");
    fscanf(stdin, "%d", &hpmax);
    int32_t cnt = 0;
    int32_t start[500];
    for(int32_t i = 0;i < GAME_SIZE;i+=4){
        uint16_t *hp_tmp = (uint16_t *)(pData + i);
        uint16_t *hpmax_tmp = (uint16_t *)(pData + i + 2);
        if(*hp_tmp == hp && *hpmax_tmp == hpmax){
            // fprintf(stdout, "%d: address: %lu");
            // printf("h\n");
            print_person((sPerson *)(pData + i - 64));
            start[cnt++] = (i - 64);
        }
        // printf("0x%x\n", pData + i);
        // break;
    }
    fprintf(stdout, "1) HP\n2) MP\n3) MT\n4) DF\n5) MV\n6) EX\n7) DX\n");
    fprintf(stdout, "Please select the content you want to modify: ");
    int32_t option = 1;
    fscanf(stdin, "%d", &option);
    sPerson person;
    memcpy(&person, (pData + start[0]), sizeof(sPerson));
    print_person(&person);
    // person
    int32_t val;
    if(option == 1){
        fprintf(stdout, "What value do you want to change HP to: ");
        fscanf(stdin, "%d", &val);
        char hexString[10];
        uint16_t hex;
        hex = val;
        // sprintf(hexString, "%x", val);
        // printf("%s\n", hexString);
        // sscanf(hexString, "%hx", &hex);
        // printf("hex: %hu\n", hex);
        person.hp = hex;
        person.hpmax = hex;
    }
    else if(option == 2){
        fprintf(stdout, "What value do you want to change MP to: ");
        fscanf(stdin, "%d", &val);
        // person.mp = val;
        person.mp = (uint16_t)150;
        person.mpmax = (uint16_t)300;
    }
    else if(option == 3){
        fprintf(stdout, "What value do you want to change MT to: ");
        fscanf(stdin, "%d", &val);
        person.mt = val;
    }
    else if(option == 4){
        fprintf(stdout, "What value do you want to change DF to: ");
        fscanf(stdin, "%d", &val);
        person.df = val;
    }
    else if(option == 5){
        fprintf(stdout, "What value do you want to change MV to: ");
        fscanf(stdin, "%d", &val);
        person.mv = val;
    }
    else if(option == 6){
        fprintf(stdout, "What value do you want to change EX to: ");
        fscanf(stdin, "%d", &val);
        person.ex = val;
    }
    else if(option == 7){
        fprintf(stdout, "What value do you want to change DX to: ");
        fscanf(stdin, "%d", &val);
        person.dx = val;
    }
    lseek(fd, addr_start + start[0], SEEK_SET);
    write(fd, &person, 80);
    lseek(fd, addr_start + start[0], SEEK_SET);
    printf("\n=========================\n");
    print_person(&person);
    fsync(fd);

    // mmap(NULL, getFDsize(fd), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    free(pData);
    close(fd);

    return 0;
}