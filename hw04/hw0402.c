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
    // {"lat", 1, NULL, 't'},
    // {"lon", 1, NULL, 'n'},
    {0, 0, 0, 0},
};
void help_interface(){
    printf("Usage: ./hw0402 [OPTIONS]\n");
    printf("Options:\n");
    printf("    -h \t\t Show this help message\n");
    printf("    -N <station_name> \t\t Search station by name\n");
    printf("    -U <uid> \t\t Search station by UID \n");
    printf("    --sna <station_name> \t\t Search station by name in Chinese\n");
    // printf("    --lat <latitude > --lon <longitude> Search nearest stations by latitude and longitude\n");
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
    int8_t _help = 0, _name = 0, _uid = 0, _lalo = 0, _sna = 0, _asked = 0;
    int32_t c;
    char name[100];
    char inp[100];
    char chinese[100];
    while((c = getopt_long(argc, argv, "hN:U:s:c:", long_options, NULL)) != -1){
        if(c == 'h'){
            _help = 1;
            _asked = 1;
        }
        else if(c == 'N'){
            _name = 1;
            _asked = 1;
            // name = optarg;
            snprintf(name, sizeof(name), optarg);
        }
        else if(c == 'U'){
            _uid = 1;
            _asked = 1;
            snprintf(inp, sizeof(inp), optarg);
        }
        else if(c == 's'){
            _sna = 1;
            _asked = 1;
            snprintf(chinese, sizeof(chinese), optarg);
        }
        // else if(c == 't'){
        //     _lalo = 1;
        //     _asked = 1;
        // }
        // else if(c == 'n'){
        //     _lalo = 1;
        //     _asked = 1;
        // }
    }
    printf("Welcome to Taipei Youbike Station Status Checker!\n");
    if(!_asked){
        printf("Search by station (N)ame , (U)id , (S)na: ");
        char inside;
        scanf("%c", &inside);
        if(inside == 'N' || inside == 'n') _name = 1;
        else if(inside == 'U' || inside == 'u') _uid = 1;
        // else if(inside == 'L' || inside == 'l') _lalo = 1;
        else if(inside == 'S' || inside =='s') _sna = 1;
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
    char sno[50], sna[50], sarea[50], mday[50], ar[50], sareaen[50], snaen[50], aren[50], act[50], srcUpdateTime[50], updateTime[50], \
    infoTime[50], infoDate[50];
    int32_t total, available_rent_bikes, available_return_bikes;
    double latitude, longitude;
    
    if(_help){
        help_interface();
    }
    else if(_name){
        if(!_asked){
            printf("Please enter the station name: ");
            
            while (getchar() != '\n');
            scanf("%[^\n]", name);
        }
        printf("(show at most 5 stations with the substring \"%s\")\n\n", name);
        char amount[1000];
        // snprintf(amount, 200, "echo \"$(cat data.json | jq '[.[] | select(.snaen | contains(\"%s\"))] | length') station(s) found with the substring \"%s\" in snaen and aren:\\n\"", name, name);
        snprintf(amount, sizeof(amount),
        "count=$(cat data.json | jq '[.[] | select((.snaen | contains(\"%s\")) or (.aren | tostring | contains(\"%s\")))] | length'); "
        "if [ \"$count\" -eq 0 ]; then "
        "echo \"No such station found\"; "
        "else "
        "echo \"$count station(s) found with the substring \\\"%s\\\" in snaen and aren:\"; "
        "cat data.json | jq -r '.[] | select((.snaen | contains(\"%s\")) or (.aren | tostring | contains(\"%s\"))) | \"UID: \\(.sno)\\nSNA: \\(.sna)\\nArea: \\(.sarea)\\nAddress: \\(.ar)\\nStation_Name: \\(.snaen)\\nAvaliable_Bikes: \\(.available_rent_bikes)\\nAvaliable_Parking_Slots: \\(.available_return_bikes)\\nLast_Update_Time: \\(.updateTime)\\n\"'; "
        "fi",
        name, name, name, name, name);
        // snprintf(amount, sizeof(amount), "cat data.json | jq -e '.[] | select((.snaen | contains(\"%s\")) or (.aren | tostring | contains(\"%s\"))) | length' && echo Found || echo \"No such station found\"", name, name);
        // snprintf(amount, 200, "echo \"$(cat data.json | jq '[.[] | select(.snaen | contains(\"%s\"))] | length') station(s) found with the substring \"%s\" in snaen and aren:\\n\"", name, name);

        system(amount);
        // char cmd[1000];
        // snprintf(cmd, sizeof(cmd), "cat data.json | jq -r '.[] | select((.snaen | contains(\"%s\")) or (.aren | tostring | contains(\"%s\"))) | \"UID: \\(.sno)\\nSNA: \\(.sna)\\nArea: \\(.sarea)\\nAddress: \\(.ar)\\nStation_Name: \\(.snaen)\\nAvaliable_Bikes: \\(.available_rent_bikes)\\nAvaliable_Parking_Slots: \\(.available_return_bikes)\\nLast_Update_Time: \\(.updateTime)\\n\"'", name, name);
        // system(cmd);
    }
    else if(_uid){
        if(!_asked){
            printf("Please enter the UID: ");
            
            while (getchar() != '\n');
            scanf("%[^\n]", inp);
        }
        printf("(show at most 5 stations with the UID \"%s\")\n\n", inp);
        char amount[500];
        // snprintf(amount, sizeof(amount), "echo \"$(cat data.json | jq '[.[] | select(.sno == \"%s\")] | length') station(s) found with the UID \"%s\":\\n\"", inp, inp);
        snprintf(amount, sizeof(amount),
        "count=$(cat data.json | jq '[.[] | select(.sno == \"%s\")]  | length'); "
        "if [ \"$count\" -eq 0 ]; then "
        "echo \"No such station found\"; "
        "else "
        "echo \"$count station(s) found with the UID \\\"%s\\\":\"; "
        "cat data.json | jq -r '.[] | select(.sno == \"%s\") | \"UID: \\(.sno)\\nSNA: \\(.sna)\\nArea: \\(.sarea)\\nAddress: \\(.ar)\\nStation_Name: \\(.snaen)\\nAvaliable_Bikes: \\(.available_rent_bikes)\\nAvaliable_Parking_Slots: \\(.available_return_bikes)\\nLast_Update_Time: \\(.updateTime)\\n\"'; "
        "fi",
        inp, inp, inp, inp, inp);
        system(amount);
        // char cmd[1000];
        // snprintf(cmd, sizeof(cmd), "cat data.json | jq -r '.[] | select(.sno == \"%s\") | \"UID: \\(.sno)\\nStation_Name: \\(.snaen)\\nAvaliable_Bikes: \\(.available_rent_bikes)\\nAvaliable_Parking_Slots: \\(.available_return_bikes)\\nLast_Update_Time: \\(.updateTime)\\n\"'", inp);
        // system(cmd);
    }
    else if(_sna){
        if(!_asked){
            printf("Please enter the station name in chinese: ");
            
            while (getchar() != '\n');
            scanf("%[^\n]", chinese);
        }
        printf("(show at most 5 stations with the substring \"%s\")\n\n", chinese);
        char amount[1000];
        // snprintf(amount, 200, "echo \"$(cat data.json | jq '[.[] | select((.ar | contains(\"%s\")) or (.sna | tostring | contains(\"%s\")))] | length') station(s) found with the substring \"%s\" in ar and sna:\\n\"", chinese, chinese, chinese);
        snprintf(amount, sizeof(amount),
        "count=$(cat data.json | jq '[.[] | select((.ar | contains(\"%s\")) or (.sna | tostring | contains(\"%s\")) or (.sarea | tostring | contains(\"%s\")))] | length'); "
        "if [ \"$count\" -eq 0 ]; then "
        "echo \"No such station found\"; "
        "else "
        "echo \"$count station(s) found with the substring \\\"%s\\\" in ar and sna and sarea:\"; "
        "cat data.json | jq -r '.[] | select((.ar | contains(\"%s\")) or (.sna | tostring | contains(\"%s\")) or (.sarea | tostring | contains(\"%s\"))) | \"UID: \\(.sno)\\nSNA: \\(.sna)\\nArea: \\(.sarea)\\nAddress: \\(.ar)\\nStation_Name: \\(.snaen)\\nAvaliable_Bikes: \\(.available_rent_bikes)\\nAvaliable_Parking_Slots: \\(.available_return_bikes)\\nLast_Update_Time: \\(.updateTime)\\n\"'; "
        "fi",
        chinese, chinese, chinese, chinese, chinese, chinese, chinese);
        // printf("%s\n", amount);
        // snprintf(amount, sizeof(amount), "cat data.json | jq -e '.[] | select((.snaen | contains(\"%s\")) or (.aren | tostring | contains(\"%s\"))) | length' && echo Found || echo \"No such station found\"", name, name);
        // snprintf(amount, 200, "echo \"$(cat data.json | jq '[.[] | select(.snaen | contains(\"%s\"))] | length') station(s) found with the substring \"%s\" in snaen and aren:\\n\"", name, name);

        system(amount);
        char cmd[1000];
        // snprintf(cmd, sizeof(cmd), "cat data.json | jq -r '.[] | select((.ar | contains(\"%s\")) or (.sna | tostring | contains(\"%s\"))) | \"UID: \\(.sno)\\nSNA: \\(.sna)\\nArea: \\(.sarea)\\nAddress: \\(.ar)\\nStation_Name: \\(.snaen)\\nAvaliable_Bikes: \\(.available_rent_bikes)\\nAvaliable_Parking_Slots: \\(.available_return_bikes)\\nLast_Update_Time: \\(.updateTime)\\n\"'", chinese, chinese);
        // system(cmd);
    }
    curl_easy_cleanup(curl);

    return 0;
}

// cat data.json | jq '.[] | select(.sno == "500101001") | "UID: \(.sno)\n Station_Name: \(.snaen)"'
// cat data.json | jq '.[] | select(.sno == "500101001") | {UID: .sno, Station_Name: .snaen, Avaliable_Bikes: .available_rent_bikes, Avaliable_Parking_Slots: .available_return_bikes, Last_Update_Time: .updateTime}'
// cat data.json | jq -r '.[] | select(.sno == "500101001") | "UID: \(.sno)\nStation_Name: \(.snaen)\nAvaliable_Bikes: \(.available_rent_bikes)\nAvaliable_Parking_Slots: \(.available_return_bikes)\nLast_Update_Time: \(.updateTime)\n"'
// cat data.json | jq -r '.[] | select(contains(["Gongguan Campus"])) | "UID: \(.sno)\nStation_Name: \(.snaen)\nAvaliable_Bikes: \(.available_rent_bikes)\nAvaliable_Parking_Slots: \(.available_return_bikes)\nLast_Update_Time: \(.updateTime)\n"'
// cat data.json | jq -r '.[] | select((.snaen | contains("Gongguan Campus")) or (.aren | tostring | contains("Gongguan Campus"))) | "UID: \(.sno)\nStation_Name: \(.snaen)\nAvaliable_Bikes: \(.available_rent_bikes)\nAvaliable_Parking_Slots: \(.available_return_bikes)\nLast_Update_Time: \(.updateTime)\n"'