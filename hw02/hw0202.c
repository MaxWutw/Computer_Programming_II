#include <stdio.h>
#include <stdint.h>
#include <string.h>
/*
win: 3pts
tie: 1pts for each
lose: 0pts
GF: total points in a contest
GA: total lost in a contest
GD: GF - GA
*/

typedef struct Team{
    char name[50];
    int32_t w, d, l, gf, ga, gd, pts;
}team;

int32_t str2num(char *str){
    int32_t ret = 0;
    for(char *it = str;*it != 0;it++){
        ret = (*it - '0') + (ret * 10);
    }
    return ret;
}

int32_t digit(int32_t num){
    int32_t ret = 0;
    while(num){
        num /= 10;
        ret++;
    }
    return ret;
}

void bubbleSortByPts(team arr[], int n) {
    for(int32_t i = 0;i < n-1; i++){
        for(int32_t j = 0;j < n-i-1; j++){
            if(arr[j].pts < arr[j+1].pts){
                team temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
            else if(arr[j].pts == arr[j+1].pts && arr[j].gd < arr[j + 1].gd){
                team temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
            else if(arr[j].pts == arr[j+1].pts && arr[j].gf < arr[j + 1].gf){
                team temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main(){
    FILE *pFile = NULL;
    char filename[150];
    fprintf(stdout, "Please enter the data file name: ");
    fscanf(stdin, "%s", filename);
    if((pFile = fopen(filename, "r+")) == NULL){
        fprintf(stderr, "Error: Unable to open file for reading and writing\n");
        return 0;
    }
    team session[800];
    int32_t idx = 0;
    char buffer[150];
    fgets(buffer, 150, pFile);
    while(!feof(pFile)){
        fgets(buffer, 150, pFile);
        char *tmp = strtok(buffer, ",");
        int32_t home = 0, away = 0;
        if(tmp != NULL) tmp = strtok(NULL, ",");
        int8_t found = 0;
        for(int32_t i = 0;i < idx;i++){
            if(strcmp(tmp, session[i].name) == 0){
                home = i;
                found = 1;
                break;
            }
        }
        if(!found){
            strcpy(session[idx].name, tmp);
            session[idx].w = 0;
            session[idx].d = 0;
            session[idx].l = 0;
            session[idx].gf = 0;
            session[idx].ga = 0;
            session[idx].gd = 0;
            session[idx].pts = 0;
            home = idx;
            idx++;
        }
        found = 0;
        if(tmp != NULL) tmp = strtok(NULL, ",");
        for(int32_t i = 0;i < idx;i++){
            if(strcmp(tmp, session[i].name) == 0){
                away = i;
                found = 1;
                break;
            }
        }
        if(!found){
            strcpy(session[idx].name, tmp);
            session[idx].w = 0;
            session[idx].d = 0;
            session[idx].l = 0;
            session[idx].gf = 0;
            session[idx].ga = 0;
            session[idx].gd = 0;
            session[idx].pts = 0;
            away = idx;
            idx++;
        }
        int32_t cnt = 0;
        if(tmp != NULL){
            int32_t home_point = 0, away_point = 0;
            tmp = strtok(NULL, ",");
            home_point = str2num(tmp);
            tmp = strtok(NULL, ",");
            away_point = str2num(tmp);
            if(home_point > away_point){
                session[home].w++;
                session[away].l++;
                session[home].pts += 3;
            }
            else if(home_point < away_point){
                session[away].w++;
                session[home].l++;
                session[away].pts += 3;
            }
            else{
                session[home].d++;
                session[away].d++;
                session[home].pts += 1;
                session[away].pts += 1;
            }
            session[home].gf += home_point;
            session[away].gf += away_point;
            session[home].ga += away_point;
            session[away].ga += home_point;
        }
    }
    fclose(pFile);
    for(int32_t i = 0;i < idx;i++){
        session[i].gd = session[i].gf - session[i].ga;
    }
    printf("    %-18s%-6s%-6s%-6s%-6s%-6s%-6s%-6s\n", "Team", "W", "D", "L", "GF", "GA", "GD", "Pts");
    bubbleSortByPts(session, idx);
    for(int32_t i = 0;i < idx;i++){
        if(i < 9)
            printf("0%d) ", i + 1);
        else printf("%d) ", i + 1);
        if(session[i].gd > 0){
            char str[20] = "";
            int32_t temp = session[i].gd, inside = session[i].gd;
            str[0] = '+';
            for(int32_t i = digit(inside);i > 0;i--){
                // if(digit(session[i].gd) == 1) printf("fdsff: %d\n", temp);
                // printf("digit: %d\n", digit(inside));
                str[i] = (temp % 10) + '0';
                temp /= 10;
            }
            str[digit(session[i].gd) + 1] = '\0';
            printf("%-14s: %3d %5d %5d %6d %5d %6s %5d\n", session[i].name, session[i].w, session[i].d, session[i].l, session[i].gf, session[i].ga, str, session[i].pts);
        }
        else
            printf("%-14s: %3d %5d %5d %6d %5d %6d %5d\n", session[i].name, session[i].w, session[i].d, session[i].l, session[i].gf, session[i].ga, session[i].gd, session[i].pts);
        // else 
        //     printf("%s: %3d %5d %5d %6d %5d %5d %5d\n", session[i].name, session[i].w, session[i].d, session[i].l, session[i].gf, session[i].ga, session[i].gd, session[i].pts);
        // printf("\n");
        // break;
    }

    return 0;
}//season-1819.csv
// 10 3 19 24 17 37 35 1