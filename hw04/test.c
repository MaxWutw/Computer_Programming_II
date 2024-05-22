#include <stdio.h>
#include <unistd.h>
int main(){
    int i;
    for(i = 0;i <= 100;i++){
        printf("Percent completed:%3d%%\r", i);
        usleep(30000);
        fflush(stdout);
    }

    return 0;
}