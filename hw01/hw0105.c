#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int32_t str2dec(char *str){
    int32_t ret = 0;
    for(char *it = str;*it != 0;it++){
        ret = (*it - '0') + (ret * 10);
    }
    return ret;
}
float str2float(char *str) {
    float ret = 0.0f;
    float fraction = 0.0f;
    int isFraction = 0;
    float divisor = 10.0f;
    int sign = 1;

    if (*str == '-') {
        sign = -1;
        str++;
    }

    for (; *str != '\0'; str++) {
        if (*str == '.') {
            isFraction = 1;
            continue;
        }
        if (isFraction) {
            fraction += (*str - '0') / divisor;
            divisor *= 10.0f;
        } else {
            ret = (ret * 10.0f) + (*str - '0');
        }
    }

    ret += fraction;
    ret *= sign;

    return ret;
}

int32_t gcd(int32_t a, int32_t b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int32_t lcm(int32_t a, int32_t b) {
    return (a * b) / gcd(a, b);
}

int32_t return_length(char *str){
    int32_t ret = 0;
    while(*str != 0){
        str++;
        if(*str == ' ' || *str == '\n' || *str == ',') continue;
        ret++;
    }
    return ret;
}
int main(){
    int32_t COURSE = 0, START = 0, beat = 4, note = 4, END, first = 1, course_first = 1;
    float BPM = 0.0, OFFSET = 0.0, duration = 0.0, pre = 0.0;
    freopen("test.in", "r", stdin);
    fprintf(stdout, "{\n");
    fprintf(stdout, "    \"data\": [\n");
    char inp[500];
    while(!feof(stdin)){
        fgets(inp, 80, stdin);
        if(inp[0] == '#'){
            char *token = strtok(inp, " /:\r\n");
            if(strcmp(token, "#START") == 0){
                START = 1;
                first = 1;
                if(!course_first) fprintf(stdout, ",\n");
                course_first = 0;
                fprintf(stdout, "        {\n");
                fprintf(stdout, "            \"course\": %d,\n", COURSE);
                fprintf(stdout, "            \"chart\": [\n");
            }
            else if(strcmp(token, "#END") == 0){
                START = 0;
                fprintf(stdout, "\n            ]\n");
                fprintf(stdout, "        }");
                duration = 0.0;
                pre = 0.0;
            }
            else if(strcmp(token, "#MEASURE") == 0){
                // printf("%s\n", token);
                token = strtok(NULL, "/");
                if(token != NULL){
                    beat = str2dec(token);
                    // printf("%d\n", beat);
                }
                token = strtok(NULL, "\r\n");
                if(token != NULL){
                    note = str2dec(token);
                    // printf("%s\n", token);
                    // printf("%d\n", note);
                }
            }
            else if(strcmp(token, "#BPMCHANGE") == 0){
                // printf("%s\n", inp);
                token = strtok(NULL, ":\n");
                BPM = str2float(token);
                // duration = (60 / BPM) * (beat / leng) * (4 / note);
                // printf("BPMCHANGE: %f\n", BPM);
            }
        }
        else if(inp[0] >= '0' && inp[0] <= '9'){
            // printf("%s\n", inp);
            int32_t leng = return_length(inp), idx = 0;
            char str[500];
            int32_t extend;
            if(leng < beat){
                extend = lcm(leng, beat);
                int32_t repeat = (extend / leng);
                int32_t idx_rep = 0;
                for(char *it = inp;*it != 0;it++){
                    if(*it == ',' || *it == '\n') continue;
                    for(int32_t i = 0;i < repeat;i++){
                        if(i == 0) str[idx_rep++] = *it;
                        else str[idx_rep++] = '0';
                    }
                }
                str[idx_rep] = 0;
            }
            else if(leng == 0){
                for(int32_t i = 0;i < beat;i++) str[i] = '0';
            }
            else{
                int32_t idx_cpy = 0;
                for(char *it = inp;*it != 0;it++){
                    if(*it == ',' || *it == '\n') continue;
                    str[idx_cpy++] = *it;
                }
                str[idx_cpy] = 0;
            }
            // printf("%d %d\n", leng, beat);
            // printf("%s\n", str);
            // continue;
            float time = 0.0;
            duration = (float)((float)60 / BPM) * ((float)beat / (float)leng) * ((float)4 / (float)note);
            for(char *it = str;*it != 0;it++){
                if(*it == '0'){
                    if(pre == 0.0) time = (duration * idx) + (-OFFSET) + pre;
                    else time = (duration * idx) + pre;
                    idx++;
                }
                if(*it == '0' || *it == ',' || *it == '\n'){
                    
                    continue;
                }
                if(pre == 0.0) time = (duration * idx) + (-OFFSET) + pre;
                else time = (duration * idx) + pre;
                if(!first){
                    fprintf(stdout, ",\n");
                }
                fprintf(stdout, "                [%c, %f]", *it, time);
                first = 0;
                idx++;
            }
            pre = time + duration;
        }
        else{
            char *token = strtok(inp, ":");
            if(strcmp(token, "BPM") == 0){
                token = strtok(NULL, ":\r\n");
                BPM = str2float(token);
                // printf("BPM: %f\n", BPM);
            }
            else if(strcmp(token, "OFFSET") == 0){
                token = strtok(NULL, ":\r\n");
                OFFSET = str2float(token);
                // printf("OFFSET: %f\n", OFFSET);
            }
            else if(strcmp(token, "COURSE") == 0){
                token = strtok(NULL, ":\r\n");
                if(strcmp(token, "Easy") == 0) COURSE = 0;
                else if(strcmp(token, "Normal") == 0) COURSE = 1;
                else if(strcmp(token, "Hard") == 0) COURSE = 2;
                else if(strcmp(token, "Oni") == 0) COURSE = 3;
                else if(strcmp(token, "Edit") == 0) COURSE = 4;
                else COURSE = token[0] - '0';
                // printf("COURSE: %d\n", COURSE);
            }
        }
    }
    fprintf(stdout, "\n    ]\n");
    fprintf(stdout, "}\n");

    return 0;
}