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

// #include "mycal.h"



// int main(){


//     char *Result = NULL;
//     int32_t return_value;

//     for(int i=2;i<=16;i++){
//         Result = NULL;
//         return_value = calculate("ABC_16",i,&Result);
//         printf("%d %s\n",return_value,Result);
//     }
    

// }

#include "mycal.h"
int main()
{
    char *pResult = NULL;
    char input[1000];
    fgets(input, 1000, stdin);
    if(input[strlen(input)-1] == '\n')
    {
        input[strlen(input)-1] = '\0';
    }
    int32_t base;
    scanf("%d", &base);
    printf("return value: %d\n", calculate(input,base, &pResult));
    printf("%s",pResult);
    free(pResult);
    return 0;

}