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

struct _sItemCodeMap{
    unsigned char code;
    char name[20];
}__attribute__ ((__packed__));
typedef struct _sItemCodeMap ItemCodeMap;

ItemCodeMap itemList[] = {
    {0x00, "短劍"},
    {0x01, "闊劍"},
    {0x02, "長劍"},
    {0x03, "巨劍"},
    {0x04, "黑暗劍"},
    {0x05, "戰士劍"},
    {0x06, "巨魔劍"},
    {0x07, "斬鐵劍"},
    {0x08, "流水劍"},
    {0x09, "大地之劍"},
    {0x0A, "龍神劍"},
    {0x0B, "炎龍劍"},
    {0x0C, "小刀"},
    {0x0D, "匕首"},
    {0x0E, "淬毒刀"},
    {0x0F, "盜賊匕首"},
    {0x10, "暗殺刀"},
    {0x11, "護手刀"},
    {0x12, "忍者刀"},
    {0x13, "地獄刀"},
    {0x14, "刺矛"},
    {0x15, "騎槍"},
    {0x16, "長戟"},
    {0x17, "先鋒矛"},
    {0x18, "斬馬刀"},
    {0x19, "惡魔之矛"},
    {0x1A, "黃金之戟"},
    {0x1B, "龍之槍"},
    {0x1C, "破魔槍"},
    {0x1D, "戰神戟"},
    {0x1E, "聖之槍"},
    {0x1F, "巨神戟"},
    {0x20, "手斧"},
    {0x21, "迴旋斧"},
    {0x22, "戰斧"},
    {0x23, "戰鎚"},
    {0x24, "巨斧"},
    {0x25, "血之斧"},
    {0x26, "閃電鎚"},
    {0x27, "狂暴之斧"},
    {0x28, "光之斧"},
    {0x29, "力量之斧"},
    {0x2A, "大地之鎚"},
    {0x2B, "魔神斧"},
    {0x2C, "短弓"},
    {0x2D, "長弓"},
    {0x2E, "黑暗弓"},
    {0x2F, "巨弓"},
    {0x30, "精靈弓"},
    {0x31, "狙擊弓"},
    {0x32, "封魔弓"},
    {0x33, "風神弓"},
    {0x34, "長棍"},
    {0x35, "釘頭鎚"},
    {0x36, "巨鎚"},
    {0x37, "槤枷"},
    {0x38, "魔法杖"},
    {0x39, "封咒杖"},
    {0x3A, "力之杖"},
    {0x3B, "黑暗杖"},
    {0x3C, "龍之杖"},
    {0x3D, "光之杖"},
    {0x3E, "鐵指套"},
    {0x3F, "鐵爪"},
    {0x40, "皇帝指環"},
    {0x41, "毒爪"},
    {0x42, "殭屍爪"},
    {0x43, "碎岩爪"},
    {0x44, "金鋼指環"},
    {0x45, "裂刃爪"},
    {0x46, "巨神指環"},
    {0x47, "魔龍爪"},
    {0x48, "威力手臂"},
    {0x49, "金鋼手臂"},
    {0x4A, "雷神手臂"},
    {0x4B, "衝擊手臂"},
    {0x4C, "光束劍"},
    {0x4D, "狙擊槍"},
    {0x4E, "光束槍"},
    {0x4F, "光束砲"},
    {0x50, "拳頭"},
    {0x51, "利爪"},
    {0x52, "觸手"},
    {0x53, "巨岩手臂"},
    {0x54, "激水砲"},
    {0x55, "風牙斬"},
    {0x56, "魔燄波"},
    {0x57, "空雷震"},
    {0x58, "聖者之戒"},
    {0x59, "勇者徽章"},
    {0x5A, "精靈契印"},
    {0x5B, "領悟之書"},
    {0x5C, "心眼之書"},
    {0x5D, "白金徽章"},
    {0x5E, "生命之實"},
    {0x5F, "魔力水晶"},
    {0x60, "風精之羽"},
    {0x61, "十字弓"},
    {0x62, "水晶弓"},
    {0x63, "雷神鞭"},
    {0x64, "天空之鑰"},
    {0x65, "傳送法杖"},
    {0x66, "修理套件"},
    {0x67, "火焰"},
    {0x68, "火神弓"},
    {0x69, "鬥神指環"},
    {0x6A, "冰焰"},
    {0x6B, "黑暗波"},
    {0x7B, "巨岩鎧"},
    {0x7C, "魔神甲"},
    {0x7F, "魔岩鎧"},
    {0x80, "布衣"},
    {0x81, "旅行裝"},
    {0x82, "精靈披風"},
    {0x83, "元素護體"},
    {0x84, "皮甲"},
    {0x85, "硬皮甲"},
    {0x86, "夜行裝"},
    {0x87, "魔法皮甲"},
    {0x88, "盜賊之衣"},
    {0x89, "忍者裝"},
    {0x8A, "潛行服"},
    {0x8B, "神祕裝"},
    {0x8C, "暗殺服"},
    {0x8D, "黑暗之衣"},
    {0x8E, "惡魔皮甲"},
    {0x8F, "雷神服"},
    {0x90, "環狀甲"},
    {0x91, "鎖子甲"},
    {0x92, "鱗甲"},
    {0x93, "連環鋼甲"},
    {0x94, "合金鎖甲"},
    {0x95, "魔法鱗甲"},
    {0x96, "血環甲"},
    {0x97, "金鋼鎖甲"},
    {0x98, "黑暗鱗甲"},
    {0x99, "力量鎖甲"},
    {0x9A, "惡魔鱗甲"},
    {0x9B, "龍鱗甲"},
    {0x9C, "鎧甲"},
    {0x9D, "銀鎧甲"},
    {0x9E, "魔法鎧甲"},
    {0x9F, "重鎧甲"},
    {0xA0, "地獄鎧甲"},
    {0xA1, "聖鎧甲"},
    {0xA2, "大地鎧甲"},
    {0xA3, "龍神鎧甲"},
    {0xA4, "長袍"},
    {0xA5, "法師袍"},
    {0xA6, "僧侶袍"},
    {0xA7, "祭師袍"},
    {0xA8, "聖者袍"},
    {0xA9, "霧之袍"},
    {0xAA, "黑暗之袍"},
    {0xAB, "天之袍"},
    {0xAC, "武道服"},
    {0xAD, "武鬥裝"},
    {0xAE, "鬥士服"},
    {0xAF, "武者鎧甲"},
    {0xB0, "妖魔鬥服"},
    {0xB1, "武神鬥服"},
    {0xB2, "戰鬥裝甲"},
    {0xB3, "突擊裝甲"},
    {0xB4, "重裝甲"},
    {0xB5, "特殊裝甲"},
    {0xB6, "硬皮"},
    {0xB7, "青色硬皮"},
    {0xB8, "龍鱗"},
    {0xB9, "勒皮"},
    {0xBA, "虛無護甲"},
    {0xBB, "王袍"},
    {0xBC, "鬥士護甲"},
    {0xBD, "地之袍"},
    {0xBE, "水之袍"},
    {0xBF, "大地裝甲"},
    {0xC0, "草藥"},
    {0xC1, "回復劑"},
    {0xC2, "再生藥"},
    {0xC3, "神聖之水"},
    {0xC4, "解毒劑"},
    {0xC5, "退麻藥"},
    {0xC6, "力量藥水"},
    {0xC7, "耐力藥水"},
    {0xC8, "速度藥水"},
    {0xC9, "綠寶石"},
    {0xCA, "紅寶石"},
    {0xCB, "藍寶石"},
    {0xCC, "鑽石"},
    {0xCD, "飛龍卵"},
    {0xCE, "魔法水"},
    {0xCF, "水晶粒"},
    {0xD0, "控制中樞"},
    {0xD1, "黃金徽章"},
    {0xD2, "星之眼"},
    {0xD3, "光之眼"},
    {0xD4, "暗之眼"},
    {0xD5, "冰之眼"},
    {0xD6, "火之眼"}
};

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
    for(int32_t i = 0;i < 16;i++){
        printf("item: %hhu\n", per->item[i]);
    }
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
    uint16_t hp, hpmax, mp, mpmax;
    lseek(fd, addr_start, SEEK_SET);
    read(fd, pData, GAME_SIZE);
    fprintf(stdout, "Please enter your current HP: ");
    fscanf(stdin, "%d", &hp);
    fprintf(stdout, "Please enter your HP maximum: ");
    fscanf(stdin, "%d", &hpmax);
    fprintf(stdout, "Please enter your current MP: ");
    fscanf(stdin, "%d", &mp);
    fprintf(stdout, "Please enter your MP maximum: ");
    fscanf(stdin, "%d", &mpmax);
    int32_t cnt = 0;
    int32_t start[500];
    for(int32_t i = 0;i < GAME_SIZE;i+=4){
        uint16_t *hp_tmp = (uint16_t *)(pData + i);
        uint16_t *hpmax_tmp = (uint16_t *)(pData + i + 2);
        uint16_t *mp_tmp = (uint16_t *)(pData + i + 4);
        uint16_t *mpmax_tmp = (uint16_t *)(pData + i + 6);
        if(*hp_tmp == hp && *hpmax_tmp == hpmax && *mp_tmp == mp && *mpmax_tmp == mpmax){
            // fprintf(stdout, "%d: address: %lu");
            // printf("h\n");
            // print_person((sPerson *)(pData + i - 64));
            start[cnt++] = (i - 64);
        }
        // printf("0x%x\n", pData + i);
        // break;
    }
    if(cnt == 0){
        fprintf(stdout, "Could not find a character matching the attributes you want to modify. Please ensure you have entered the correct character attributes you wish to modify.\n");
        return 0;
    }
    fprintf(stdout, "1) HP\n2) MP\n3) MT\n4) DF\n5) MV\n6) EX\n7) DX\n8) cancel\n");
    fprintf(stdout, "Please select the abilities you want to modify: ");
    int32_t option = 1;
    fscanf(stdin, "%d", &option);
    sPerson person;
    memcpy(&person, (pData + start[0]), sizeof(sPerson));
    for(int32_t i = 0;i < cnt;i++){
        memcpy(&person, (pData + start[i]), sizeof(sPerson));
        // print_person(&person);
        // person
        int32_t val;
        if(option == 1){
            if(i == 0){
                fprintf(stdout, "What value do you want to change HP to: ");
                fscanf(stdin, "%d", &val);
            }
            uint16_t hex;
            hex = val;
            person.hp = hex;
            person.hpmax = hex;
        }
        else if(option == 2){
            if(i == 0){
                fprintf(stdout, "What value do you want to change MP to: ");
                fscanf(stdin, "%d", &val);
            }
            person.mp = (uint16_t)val;
            person.mpmax = (uint16_t)val;
        }
        else if(option == 3){
            if(i == 0){
                fprintf(stdout, "What value do you want to change MT to: ");
                fscanf(stdin, "%d", &val);
            }
            person.mt = (uint16_t)val;
        }
        else if(option == 4){
            if(i == 0){
                fprintf(stdout, "What value do you want to change DF to: ");
                fscanf(stdin, "%d", &val);
            }
            person.df = (uint16_t)val;
        }
        else if(option == 5){
            if(i == 0){
                fprintf(stdout, "What value do you want to change MV to: ");
                fscanf(stdin, "%d", &val);
            }
            person.mv = (uint16_t)val;
        }
        else if(option == 6){
            if(i == 0){
                fprintf(stdout, "What value do you want to change EX to: ");
                fscanf(stdin, "%d", &val);
            }
            person.ex = (uint16_t)val;
        }
        else if(option == 7){
            if(i == 0){
                fprintf(stdout, "What value do you want to change DX to: ");
                fscanf(stdin, "%d", &val);
            }
            person.dx = (uint16_t)val;
        }
        else break;
        lseek(fd, addr_start + start[i], SEEK_SET);
        write(fd, &person, 80);
        lseek(fd, addr_start + start[i], SEEK_SET);
        // printf("\n=========================\n");
        // print_person(&person);
        fsync(fd);
    }
    int32_t numItems = sizeof(itemList) / sizeof(ItemCodeMap);
    for(int32_t i = 0;i < numItems;i++){
        printf("%d) %s\n", i + 1, itemList[i].name);
    }
    // printf("%d) Cancel\n", numItems + 1);
    int32_t num = 1;
    fprintf(stdout, "Please select the items number you want to equipment: ");
    fscanf(stdin, "%d", &num);
    num--;
    if(num == numItems){
        fprintf(stdout, "The modifications are complete. Wishing you smooth gaming ahead.\n");
        return 0;
    }
    else if(num > numItems){
        fprintf(stdout, "The modifications are complete. Wishing you smooth gaming ahead.\n");
        return 0;
    }
    // print_person(&person);
    for(int32_t i = 0;i < cnt;i++){
        memcpy(&person, (pData + start[i]), sizeof(sPerson));
        int8_t judge = 1;
        for(int32_t j = 0;j < 16;j+=2){
            if((int32_t)person.item[j] == 128){
                person.item[j] = 64;
                person.item[j + 1] = itemList[num].code;
                judge = 0;
                break;
            }
        }
        print_person(&person);
        if(judge){
            fprintf(stdout, "Your inventory is full, unable to add more equipment.\n");
            break;
        }
        lseek(fd, addr_start + start[i], SEEK_SET);
        write(fd, &person, 80);
        lseek(fd, addr_start + start[i], SEEK_SET);
        // printf("\n=========================\n");
        // print_person(&person);
        fsync(fd);
    }
    // printf("\ncnt : %d\n", cnt);
    free(pData);
    close(fd);
    fprintf(stdout, "The modifications are complete. Wishing you smooth gaming ahead.\n");

    return 0;
}