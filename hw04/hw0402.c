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
    printf("Options:\n")
    printf("    -h \t\t Show this help message\n");
    printf("    -N <station_name> \t\t Search station by name\n");
    printf("    -U <uid> \t\t Search station by UID \n");
    printf("    --sna <station_name> \t\t Search station by name in Chinese\n");
    printf("    --lat <latitude > --lon <longitude> Search nearest stations by latitude and longitude")
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
    printf("welcome to Taipei Youbike Station Status Checker!\n");
    printf("search by station (N)ame , (U)id , (L)atitude and longitude: N\n");
    int8_t _help = 0, _name = 0, _uid = 0, _lalo = 0, _sna = 0;
    while((c = getopt_long(argc, argv, "hN:U:s:t:n:", long_options, NULL)) != -1){
        if(c == 'h'){
            _help = 1;
        }
        else if(c == 'N'){
            _name = 1;
            timeinterval = str2int(optarg);
        }
        else if(c == 'U'){
            _uid = 1;
            expid = str2int(optarg);
        }
        else if(c == 's'){
            _sna = 1;
            counttime = str2int(optarg);
        }
        else if(c == 't'){
            _lalo = 1;
            counttime = str2int(optarg);
        }
        else if(c == 'n'){
            _lalo = 1;
            counttime = str2int(optarg);
        }
    }

    CURL *curl;
    CURLcode res;
 
    curl = curl_easy_init();
    if(curl){
        curl_easy_setopt( curl, CURLOPT_URL, "https://tcgbusfs.blob.core.windows.net/dotapp/youbike/v2/youbike_immediate.json" );

    }
    if(_help){
        help_interface();
    }
    else if(_name){
        printf("Please enter the station name: ");
        char name[100];
        scanf("%s", name);
        printf("(show at most 5 stations with the substring \"%s\")\n");

    }
    else if(_uid){

    }
    else if(_lalo){

    }
    else if(_sna){

    }
    
    return 0;
}
