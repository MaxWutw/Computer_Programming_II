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
struct option long_options[] = {
    {"help", 0, NULL, 'h'},
    {"time-interval", 1, NULL, 't'},
    {"pid", 1, NULL, 'p'},
    {"count", 1, NULL, 'c'},
    {0, 0, 0, 0},
};
void help_interface(){
    printf("Usage: hw0401 [options]\n");
    printf("    -t, --time-interval=time \t Update the information every [time] seconds.Default: 5 seconds\n");
    printf("    -c, --count \t Update the information [count] times. Default: infinite\n");
    printf("    -p, --pid=pid \t Only display the given process information.\n");
    printf("    -h, --help \t Display this information and exit.\n");
}
// int32_t str2int(char str[50]){
//     int32_t res = 0;
//     for(char *it = str;*it != '\0';it++){
//         res = (*it - '\0') + res * 10;
//     }
//     return res;
// }
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
    int8_t _help = 0, _tim = 0, _pid = 0, _cnt = 0;
    int32_t expid = 0;
    int32_t c, timeinterval = 0, counttime = 0;
    while((c = getopt_long(argc, argv, "ht:p:c:", long_options, NULL)) != -1){
        if(c == 'h'){
            _help = 1;
        }
        else if(c == 't'){
            _tim = 1;
            timeinterval = str2int(optarg);
        }
        else if(c == 'p'){
            _pid = 1;
            expid = str2int(optarg);
        }
        else if(c == 'c'){
            _cnt = 1;
            counttime = str2int(optarg);
        }
    }
    if(_help && (_tim || _pid || _cnt)){
        fprintf(stderr, "Error: You should only select one option, if you want to get the help information.\n");
        return 0;
    }
    else if(_help){
        help_interface();
        return 0;
    }
    while(1){
        DIR *procdir;
        struct dirent *entry;
        FILE *pFile;
        char path[500];
        int32_t pid = 0;
        int64_t mem = 0;
        char name[500], state;
        int32_t utime, stime, cutime, cstime, starttime;
        int32_t forcnt = 0;
        printf("PID          %30s          state          CPU              MEM\n", "NAME");
        procdir = opendir("/proc");
        if(!procdir){
            fprintf(stdout, "Error: opendir failed");
            return 0;
        }
        FILE *pUptime = fopen("/proc/uptime", "r");
        while((entry = readdir(procdir))){
            if(!isdigit(entry->d_name[0])) continue;
            
            // printf("%s\n", entry->d_name);
            double uptime = 0;
            char buffer[100];
            fread(buffer, 20, 1, pUptime);
            sscanf(buffer, "%lf %*s", &uptime);
            // printf("%*s\n", buffer);
            snprintf(path, sizeof(path), "/proc/%s/stat", entry->d_name);
            pFile = fopen(path, "r");
            fscanf(pFile, "%d %[^)]) %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %d %d %d %d %*d %*d %*d %*d %d %ld %*d %*d %*s", &pid, name, &state, &utime, &stime, &cutime, &cstime, &starttime, &mem);
            int32_t Hertz = sysconf(_SC_CLK_TCK);
            double total_time = utime + stime + cutime + cstime;
            double seconds = uptime - ((double)starttime / (double)Hertz);
            // printf("%lf\n", uptime);
            double cpu_usage = 100 * ((total_time / (double)Hertz) /  seconds);
            if(_pid){
                if(str2int(entry->d_name) == expid){
                    printf("%d          %30s)              %c          %lf          %ld\n", pid, name, state, cpu_usage, mem);
                    break;
                }
            }
            else{
                printf("%d          %30s)              %c          %lf          %ld\n", pid, name, state, cpu_usage, mem);
            }
        }
        if(_tim){
            sleep(timeinterval);
        }
        else sleep(5);
        closedir(procdir);
        fclose(pUptime);
        fclose(pFile);
        if(_cnt){
            if(counttime--) continue;
            else break;
        }
        system("clear");
    }
    
    return 0;
}
