#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define RESET "\033[0m"
float str2sec(char *str){
    float total = 0.0;
    float ret = 0.0;
    while(*str != ':'){
        ret = (*str - '0') + ret * 10;
        str++;
    }
    str++;
    total += (ret * 3600);
    ret = 0;
    while(*str != ':'){
        ret = (*str - '0') + ret * 10;
        str++;
    }
    str++;
    total += (ret * 60);
    ret = 0;
    total += strtod(str, NULL);
    // printf("%c\n", *str);
    // printf("total: %f\n", total);
    return total;
}

int32_t set_color(const char *str){
    int32_t val = 0;
    if(str[0] == '&' && str[1] == 'H'){
        str += 2;
        sscanf(str, "%x", &val);
    }
    else{
        while(*str != 0){
            val = (*str - '0') + (val * 10);
            str++;
        }
    }
    return val;
}

int main(){
    // freopen("test.in", "r", stdin);
    FILE *pFile;
    char filename[50];
    int32_t time_shift = 0;
    float speed = 0.0;
    int32_t red, green, blue;
    fprintf(stdout, "Please enter the file name: ");
    fscanf(stdin, "%s", filename);
    fprintf(stdout, "Time Shift ( -10 ~ 10 ): ");
    fscanf(stdin, "%d", &time_shift);
    if(time_shift < -10 | time_shift > 10){
        fprintf(stderr, "The time shift should between -10 and 10\n");
        return 0;
    }
    printf("%d\n", time_shift);
    speed = 2;
    fprintf(stdout, "Speed (0.25 ,0.5 ,0.75 ,1 ,1.25 ,1.5 ,1.75 ,2): ");
    fscanf(stdin, "%f", &speed);
    if(speed != 0.25 && speed != 0.5 && speed != 0.75 && speed != 1 && speed != 1.25 && speed != 1.5 && speed != 1.75 && speed != 2){
        fprintf(stderr, "The speed should be 0.25 ,0.5 ,0.75 ,1 ,1.25 ,1.5 ,1.75 ,2!\n");
        return 0;
    }
    if((pFile = fopen(filename, "r")) == NULL){
        fprintf(stderr, "Error: Unable to open file for reading and writing\n");
        return 0;
    }
    float time_cur = (float)time_shift;
    while(!feof(pFile)){
        // printf("fdsfa");
        char buffer[500];
        fgets(buffer, 450, pFile);
        char *str = strtok(buffer, ":");
        if(strcmp(str, "Style") == 0){
            int32_t cnt = 4;
            while(cnt--){
                if(str != NULL) str = strtok(NULL, ",");
            }
            int32_t color_value = set_color(str);
            red = (color_value >> 16) & 0xFF;
            green = (color_value >> 8) & 0xFF;
            blue = color_value & 0xFF;
            // printf("%d\n", color_value);
        }
        if(strcmp(str, "Dialogue") == 0){
            if(str != NULL) str = strtok(NULL, ",");
            if(str != NULL) str = strtok(NULL, ",");
            if(str != NULL){
                float start = str2sec(str), end = 0.0;
                if(str != NULL) str = strtok(NULL, ",");
                end = str2sec(str);
                if(end > time_cur){
                    // printf("%f\n", start);
                    if(start >= time_cur) sleep((start - time_cur) / speed);
                    else sleep((time_cur - start) / speed);
                    time_cur = start;
                    
                    // printf("%s\n", str);
                    // end = str2sec(str);
                    int32_t cnt = 4;
                    while(cnt--){
                        if(str != NULL) str = strtok(NULL, ",");
                        // printf("%s\n", str);
                    }
                    str += 3;
                    printf("\033[38;2;%d;%d;%dm", blue, green, red);
                    printf("%s", str);
                    printf("\033[0m");
                    // printf("%f\n", end);
                    sleep((end - start) / speed);
                    time_cur = end;
                }
                system("clear");
            }
        }
    }

    return 0;
}