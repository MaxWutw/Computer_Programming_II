#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
float al2prob(char a){
    if(a == 'A' || a == 'a') return 8.2;
    else if(a == 'B' || a == 'b') return 1.5;
    else if(a == 'C' || a == 'c') return 2.8;
    else if(a == 'D' || a == 'd') return 4.3;
    else if(a == 'E' || a == 'e') return 12.7;
    else if(a == 'F' || a == 'f') return 2.2;
    else if(a == 'G' || a == 'g') return 2.0;
    else if(a == 'H' || a == 'h') return 6.1;
    else if(a == 'I' || a == 'i') return 7.0;
    else if(a == 'J' || a == 'j') return 0.15;
    else if(a == 'K' || a == 'k') return 0.77;
    else if(a == 'L' || a == 'l') return 4.0;
    else if(a == 'M' || a == 'm') return 2.4;
    else if(a == 'N' || a == 'n') return 6.7;
    else if(a == 'O' || a == 'o') return 7.5;
    else if(a == 'P' || a == 'p') return 1.9;
    else if(a == 'Q' || a == 'q') return 0.095;
    else if(a == 'R' || a == 'r') return 6.0;
    else if(a == 'S' || a == 's') return 6.3;
    else if(a == 'T' || a == 't') return 9.1;
    else if(a == 'U' || a == 'u') return 2.8;
    else if(a == 'V' || a == 'v') return 0.98;
    else if(a == 'W' || a == 'w') return 2.4;
    else if(a == 'X' || a == 'x') return 0.15;
    else if(a == 'Y' || a == 'y') return 2.0;
    else if(a == 'Z' || a == 'z') return 0.074;
    else return 0.0; 
}
int main(){
    fprintf(stdout, "Advice:   EERIE\n");
    FILE *pFile;
    char fail[800], not1[800], not2[800], not3[800], not4[800], not5[800];
    int32_t fail_idx = 0, n1_idx = 0, n2_idx = 0, n3_idx = 0, n4_idx = 0, n5_idx = 0;
    if((pFile = fopen("en_US.dic", "r")) == NULL){
        fprintf(stderr, "Error: Unable to open file for reading and writing\n");
        return 0;
    }
    char feedback[10], alphabet[10], position[10], guess[10] = "EERIE";
    // int32_t total[30];
    int32_t alpha = 0;
    for(int32_t i = 0;i < 5;i++){
        position[i] = 0;
        alphabet[i] = 0;
    }
    // for(int32_t i = 0;i < 30;i++){
    //     total[i] = 0;
    // }
    while(1){
        fprintf(stdout, "Feedback: ");
        fscanf(stdin, "%s", feedback);
        if(strcmp(feedback, "GGGGG") == 0){
            fprintf(stdout, "Congratulations!!\n");
            return 0;
        }
        // EERIE YBYBB
        float probability = 0.0;
        for(int32_t i = 0;i < 5;i++){
            if(feedback[i] == 'B'){
                // fail[fail_idx] = tolower(guess[i]);
                // fail_idx++;
                int8_t ctrl = 1;
                for(int32_t j = 0;j < 5;j++){
                    if(guess[i] == guess[j] && feedback[j] == 'Y') ctrl = 0;
                }
                if(ctrl){
                    fail[fail_idx] = tolower(guess[i]);
                    fail_idx++;
                }
                if(i == 0){
                    not1[n1_idx] = tolower(guess[i]);
                    n1_idx++;
                }
                else if(i == 1){
                    not2[n2_idx] = tolower(guess[i]);
                    // printf("%c\n", guess[i]);
                    n2_idx++;
                }
                else if(i == 2){
                    not3[n3_idx] = tolower(guess[i]);
                    n3_idx++;
                }
                else if(i == 3){
                    not4[n4_idx] = tolower(guess[i]);
                    n4_idx++;
                }
                else if(i == 4){
                    not5[n5_idx] = tolower(guess[i]);
                    n5_idx++;
                }
            }
            else if(feedback[i] == 'G'){
                // total[tolower(guess[i]) - 'a'] = 1;
                position[i] = tolower(guess[i]);
            }
            else if(feedback[i] == 'Y'){
                if(i == 0){
                    not1[n1_idx] = tolower(guess[i]);
                    n1_idx++;
                }
                else if(i == 1){
                    not2[n2_idx] = tolower(guess[i]);
                    // printf("%c\n", guess[i]);
                    n2_idx++;
                }
                else if(i == 2){
                    not3[n3_idx] = tolower(guess[i]);
                    n3_idx++;
                }
                else if(i == 3){
                    not4[n4_idx] = tolower(guess[i]);
                    n4_idx++;
                }
                else if(i == 4){
                    not5[n5_idx] = tolower(guess[i]);
                    n5_idx++;
                }
                // total[tolower(guess[i]) - 'a'] = 1;
                alphabet[alpha] = tolower(guess[i]);
                alpha++;
            }
            else{
                fprintf(stderr, "ERROR INPUT! Your input must be G or Y or B.\n");
                return 0;
            }
        }
        // for(int32_t i = 0;i < fail_idx;i++) printf("%c ", fail[i]);
        // printf("\n");
        // for(int32_t i = 0;i < alpha;i++) printf("%c ", alphabet[i]);
        while(!feof(pFile)){
            char buf[100];
            fgets(buf, 80, pFile);
            // printf("%s\n", buf);
            char *str = strtok(buf, "/\n");
            // printf("%s\n", str);
            if(strlen(str) != 5) continue;
            int8_t out = 0;
            int32_t tmp_idx = 0;
            for(const char *it = str;*it != 0;it++){
                for(int32_t i = 0;i < fail_idx;i++){
                    if(fail[i] == tolower(*it) && feedback[tmp_idx] != 'G'){
                        // printf("%s\n", str);
                        out = 1;
                        break;
                    }
                }
                tmp_idx++;
                if(out) break;
            }
            if(out) continue;
            int8_t tmp_judge = 0;
            // for(const char *it = str;*it != 0;it++){
            //     if(not[not_idx] != 0 && not[not_idx] == tolower(*it)){
            //         tmp_judge = 1;
            //         break;
            //     }
            //     not_idx++;
            // }
            // printf("number: %d %d %d %d %d\n", n1_idx, n2_idx, n3_idx, n4_idx, n5_idx);
            for(int32_t i = 0;i < 5;i++){
                // if(not[i] != 0 && not[i] == tolower(str[i])){
                //     printf("%c\n", not[i]);
                //     tmp_judge = 1;
                //     break;
                // }
                if(i == 0){
                    for(int32_t j = 0;j < n1_idx;j++){
                        if(not1[j] == tolower(str[i])){
                            tmp_judge = 1;
                            break;
                        }
                    }
                }
                else if(i == 1){
                    // printf("%c\n", tolower(str[1]));
                    for(int32_t j = 0;j < n2_idx;j++){
                        // printf("%c\n", tolower(str[i]));
                        if(not2[j] == tolower(str[i])){
                            // printf("not\n");
                            tmp_judge = 1;
                            break;
                        }
                    }
                }
                else if(i == 2){
                    for(int32_t j = 0;j < n3_idx;j++){
                        if(not3[j] == tolower(str[i])){
                            tmp_judge = 1;
                            break;
                        }
                    }
                }
                else if(i == 3){
                    for(int32_t j = 0;j < n4_idx;j++){
                        if(not4[j] == tolower(str[i])){
                            tmp_judge = 1;
                            break;
                        }
                    }
                }
                else if(i == 4){
                    for(int32_t j = 0;j < n5_idx;j++){
                        if(not5[j] == tolower(str[i])){
                            tmp_judge = 1;
                            break;
                        }
                    }             
                }
                if(tmp_judge) break;
            }
            if(tmp_judge) continue;
            int8_t test = 0;
            for(int32_t i = 0;i < alpha;i++){
                test = 1;
                for(const char *it = str;*it != 0;it++){
                    if(alphabet[i] == tolower(*it)){
                        test = 0;
                        // printf("%c\n", alphabet[i]);
                        break;
                    }
                }
                if(test) break;
            }
            if(test) continue;
            int32_t idx = 0;
            int8_t judge = 1;
            float tmp = 0.0;
            // printf("str: %s\n", str);
            int8_t pos = 0;
            for(const char *it = str;*it != 0;it++){
                if(position[idx] != 0 && position[idx] != tolower(*it)){
                    pos = 1;
                    break;
                }
                // printf("%c", *it);
                tmp += al2prob(*it);
                idx++;
            }
            if(pos) continue;
            if(tmp > probability + 0.0000001){
                // printf("%f\n", tmp);
                probability = tmp;
                strcpy(guess, str);
            }
            // printf("%s\n", str);
        }
        probability = 0.0;
        fprintf(stdout, "Advice:   ");
        for(int32_t i = 0;i < 5;i++){
            fprintf(stdout, "%c", toupper(guess[i]));
        }
        printf("\n");
        rewind(pFile);
    }
    

    return 0;
}