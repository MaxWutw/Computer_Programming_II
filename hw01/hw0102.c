// #include <stdio.h>
// #include <stdlib.h>
// #include "mycal.h"
// int main(){
//     char *str;
//     char *data = "ABC_16 + 00010_2 * 13_10 * ABC_16";
//     // calculate(data, 10, &str);
//     // char *num = "01011_2";
//     // printf("%d\n", convert2base10(data));
//     calculate(data, 16, &str);

//     return 0;
// }

#include "mycal.h"



int main(){

    
    char *Result = NULL;
    int32_t return_value = calculate("1_12 - 35_10",10,&Result);
    printf("%d %s\n",return_value,Result);
    // free(Result);
    Result = NULL;
    return_value = calculate("1_12 - 35_10",3,&Result);
    printf("%d %s\n",return_value,Result);
    // free(Result);
    Result = NULL;
    return_value = calculate("1892_10 * 100_2",10,&Result);
    printf("%d %s\n",return_value,Result);
    // free(Result);
    Result = NULL;
    return_value = calculate("ABC_16 + 00001_2 * 10_10 - 9_10 + AAAAB_12 * 00010_2 + CCA_13 * 5_10",10,&Result);
    printf("%d %s\n",return_value,Result);
    // free(Result);
    Result = NULL;

    
    // return_value = calculate("ABC_16 + 00001_2 * 10_10 - 9_10 + AAAAB_12 * 00010_2 + CCA_13 * 5_10",16,&Result);
    // printf("%d %s\n",return_value,Result);
    // Result = NULL;
    // return_value = calculate("ABC_16 + 00001_2 * 10_10 - 9_10 + AAAAB_12 * 00010_2 + CCA_13 * 5_10",7,&Result);
    // printf("%d %s\n",return_value,Result);
    // Result = NULL;
    // return_value = calculate("ABC_2 + 00001_2 * 10_10 - 9_10 + AAAAB_12 * 00010_2 + CCA_13 * 5_10",7,&Result);
    // printf("%d %s\n",return_value,Result);
    // Result = NULL;
    // return_value = calculate("ABC_16 + 00001_2 * 10_10 -9_10 + AAAAB_12 * 00010_2 + CCA_13 * 5_10",9,&Result);
    // printf("%d %s\n",return_value,Result);
    // Result = NULL;
    // return_value = calculate("ABC_16 + 00001_2 * 10_10 - 9_10 + AAAAB_12 * 00010_2 + CCA_13 * 5_10",9,&Result);
    // printf("%d %s\n",return_value,Result);

}
