#include <stdio.h>
#include <stdlib.h>
#define Peval(cmd) printf(#cmd ": %g\n", cmd);

int main(){
    double *plist = (double[]){1, 2, 3};
    double list[] = {1, 2, 3};
    // Peval(sizeof(plist) / (sizeof(double) + 0.0));
    // printf("sizeof(plist) / (sizeof(double) + 0.0)" ": %g\n", sizeof(plist) / (sizeof(double) + 0.0));
    // Peval(sizeof(list) / (sizeof(double) + 0.0));
    int32_t a = 10;
    int32_t *ptr = malloc(100 * sizeof(int32_t));
    int32_t arr[100];
    printf("%d\n", sizeof(ptr));
    printf("%d\n", sizeof(arr));

    return 0;
}