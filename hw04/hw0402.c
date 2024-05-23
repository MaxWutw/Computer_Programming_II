#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <ctype.h>
#include <curl/curl.h>
#include <assert.h>
struct option long_options[] = {
    {"help", 0, NULL, 'h'},
    {"Name", 1, NULL, 'N'},
    {"UID", 1, NULL, 'U'},
    {"sna", 1, NULL, 's'},
    {"lat", 1, NULL, 't'},
    {"lon", 1, NULL, 'n'},
    {0, 0, 0, 0},
};
void help_interface(){
    printf("Usage: ./hw0402 [OPTIONS]\n");
    printf("Options:\n");
    printf("    -h \t\t Show this help message\n");
    printf("    -N <station_name> \t\t Search station by name\n");
    printf("    -U <uid> \t\t Search station by UID \n");
    printf("    --sna <station_name> \t\t Search station by name in Chinese\n");
    printf("    --lat <latitude > --lon <longitude> Search nearest stations by latitude and longitude");
}

int32_t str2int(const char *str) {
    char *endptr;
    long val = strtol(str, &endptr, 10);
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid number: %s\n", str);
        exit(EXIT_FAILURE);
    }
    return (int32_t)val;
}
int main(int argc, char *argv[]){
    printf("Welcome to Taipei Youbike Station Status Checker!\n");
    printf("Search by station (N)ame , (U)id , (L)atitude and longitude: ");
    char inp;
    scanf("%c", &inp);
    int8_t _help = 0, _name = 0, _uid = 0, _lalo = 0, _sna = 0;
    int32_t c;
    if(inp == 'N' || inp == 'n') _name = 1;
    else if(inp == 'U' || inp == 'u') _uid = 1;
    else if(inp == 'L' || inp == 'l') _lalo = 1;
    while((c = getopt_long(argc, argv, "hN:U:s:t:n:", long_options, NULL)) != -1){
        if(c == 'h'){
            _help = 1;
        }
        else if(c == 'N'){
            _name = 1;
        }
        else if(c == 'U'){
            _uid = 1;
        }
        else if(c == 's'){
            _sna = 1;
        }
        else if(c == 't'){
            _lalo = 1;
        }
        else if(c == 'n'){
            _lalo = 1;
        }
    }

    CURL *curl;
    CURLcode res;
 
    curl = curl_easy_init();
    if(curl){
        curl_easy_setopt( curl, CURLOPT_URL, "https://tcgbusfs.blob.core.windows.net/dotapp/youbike/v2/youbike_immediate.json" );
        FILE *pFile = fopen( "data.json", "w" );
        assert( pFile );
        curl_easy_setopt( curl, CURLOPT_WRITEDATA, pFile );
        
        /* Perform the request, res will get the return code */ 
        res = curl_easy_perform(curl);
        /* Check for errors */ 
        if( res != CURLE_OK )
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        fclose(pFile);
    }
    FILE *pFile = fopen( "data.json", "r" );
    char sno[50], sna[50], sarea[50], mday[50], ar[50], sareaen[50], snaen[50], aren[50], act[50], srcUpdateTime[50], updateTime[50], \
    infoTime[50], infoDate[50];
    int32_t total, available_rent_bikes, available_return_bikes;
    double latitude, longitude;
    
    if(_help){
        help_interface();
    }
    else if(_name){
        printf("Please enter the station name: ");
        char name[100];
        scanf("%s", name);
        printf("(show at most 5 stations with the substring \"%s\")\n", name);
        int32_t cnt = 0;
        char tmp[10];
        fread(tmp, 1, 1, pFile);
        while(pFile){
            char buffer[4096];
            fread(tmp, 1, 1, pFile);
            fread(buffer, 1, 20, pFile);
            printf("%s\n", buffer);
            break;
            sscanf(buffer, "%*[^:]:%[^,],%*[^:]:%[^,],%*[^:]:%[^,],%*[^:]:%[^,],%*[^:]:%[^,],%*[^:]:%[^,],\
            %*[^:]:%[^,],%*[^:]:%[^,],%*[^:]:%[^,],%*[^:]:%[^,],%*[^:]:%[^,],%*[^:]:%[^,],%*[^:]:%[^,],\
            %*[^:]:%d,%*[^:]:%d,%*[^:]:%lf,%*[^:]:%lf,%*[^:]:%d",\
            sno, sna, sarea, mday, ar, sareaen, snaen, aren, act, srcUpdateTime, updateTime, infoTime, infoDate, &total,\
            &available_rent_bikes, &latitude, &longitude, &available_return_bikes);
            // printf("%s  %s\n", snaen, name);
            // printf("%s\n", sno);
            if(strstr(snaen, name) != NULL){
                printf("UID: %s\n", sno);
                printf("Station Name: %s\n", snaen);
                printf("Avaliable Bikes: %d\n", available_rent_bikes);
                printf("Avaliable Parking Slots: %d\n", available_return_bikes);
                printf("Last Update Time: %s\n\n", updateTime);
                cnt++;
            }
            fread(tmp, 1, 2, pFile);
        }
    }
    else if(_uid){

    }
    else if(_lalo){

    }
    else if(_sna){

    }
    curl_easy_cleanup(curl);
    fclose(pFile);

    return 0;
}
