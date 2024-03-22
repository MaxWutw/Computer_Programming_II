// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "mystring.h"
// int main(){
//     // const char *str1 = "This is a c-style string";
//     // const char *str2 = "c-style";
//     // int siz = mystrpbrk(str1, str2);
//     // printf("%d\n", siz);
//     // char *str = mystrstr(str1, str2);
//     // printf("%s\n", str);
//     char str[] = "Hello world, nice to meet you";
//     const char* d = "  ,";
//     char *p;
//     p = mystrtok(str, d);
//     // char *str1 = "hello";
//     // char *str2 = str1;
//     // str2 = ";";
//     // printf("%s\n", str1);
//     // printf("%s\n", p);
//     while (p != NULL) {
//         printf("%s\n", p);
//         p = mystrtok(NULL, d);		   
//     }

//     return 0;
// }
// // #include <stdio.h>
// // #include <string.h>
// // int main()
// // {
// //     int len;
// //     // initializing strings
// //     const char *s1 = "abcdefg book";
// //     const char *s2 = "c";
// //     // using strcspn() to compute initial chars
// //     // before 1st matching chars.
// //     // returns 3
// //     len = strcspn(s1, s2);
// //     printf("length of string that characters not present in s2: %d\n", len);
// //     return 0;
// // }



#include "mystring.h"
#include <string.h>
int main()
{

    while (1)
    {
        int type = 0;
        char input[1000];
        char inputcpy[1000];
        scanf("%d", &type);
        char *compS;
        char *compC;
        switch (type)
        {
        case 0:
            return 0;
        case -1:
            printf("mystrchr\n");
            compC = mystrchr("abcdedf", 'e');
            compS = strchr("abcdedf", 'e');
            printf("%s\n", *compC == *compS ? "true" : "false");
            break;
        case 1:
            printf("mystrchr\n");
            scanf("%s", input);
            sscanf(input, "%s", inputcpy);
            char c;
            scanf("%c", &c);
            compC = mystrchr(input, c);
            compS = strchr(inputcpy, c);
            if(compS == NULL && compC == NULL){
                printf("true\n");
                break;
            }
            else if((compS == NULL && compC != NULL) || \
            (compS != NULL && compC == NULL)){
                printf("true\n");
                break;
            }
            printf("%s\n", *compC == *compS ? "true" : "false");
            for (size_t i = 0; i < strlen(input); i++)
            {
                printf("%d", compC[i] == compS[i]);
            }
            printf("\n");
            break;
        case -2:
            printf("mystrrchr\n");
            compC = mystrrchr("abcdedf", 'e');
            compS = strrchr("abcdedf", 'e');
            printf("%s\n", *compC == *compS ? "true" : "false");
            break;
        case 2:
            printf("mystrrchr\n");
            scanf("%s", input);
            sscanf(input, "%s", inputcpy);
            char c2;
            scanf("%c", &c2);
            compC = mystrrchr(input, c2);
            compS = strrchr(inputcpy, c2);
            printf("%s\n", *compC == *compS ? "true" : "false");
            for (size_t i = 0; i < strlen(compC); i++)
            {
                printf("%d", compC[i] == compS[i]);
            }
            printf("\n");
            break;
        case -3:
            printf("mystrpbrk\n");
            compC = mystrpbrk("abcdedf", "ed");
            compS = strpbrk("abcdedf", "ed");
            printf("%s\n", *compC == *compS ? "true" : "false");
            break;
        case 3:
            printf("mystrpbrk\n");
            scanf("%s", input);
            sscanf(input, "%s", inputcpy);
            char c3[1000];
            scanf("%s", c3);
            compC = mystrpbrk(input, c3);
            compS = strpbrk(inputcpy, c3);
            for (size_t i = 0; i < strlen(compC); i++)
            {
                printf("%d", compC[i] == compS[i]);
            }
            printf("\n");
            break;
        case -4:
            printf("mystrspn\n");
            printf("%s\n", mystrspn("abcdedf", "ed") == strspn("abcdedf", "ed") ? "true" : "false");

            break;

        case 4:
            printf("mystrspn\n");
            scanf("%s", input);
            sscanf(input, "%s", inputcpy);
            char c4[1000];
            scanf("%s", c4);
            printf("%s\n", mystrspn(input, c4) == strspn(inputcpy, c4) ? "true" : "false");
            printf("original: %s\n", strcmp(input,inputcpy)==0 ? "true" : "false");
            break;
        case -5:
            printf("mystrcspn\n");
            printf("%s\n", mystrcspn("abcdedf", "ed") == strcspn("abcdedf", "ed") ? "true" : "false");

            break;
        case 5:
            printf("mystrcspn\n");
            scanf("%s", input);
            sscanf(input, "%s", inputcpy);
            char c5[1000];
            scanf(" %s", c5);
            printf("%s\n", mystrcspn(input, c5) == strcspn(inputcpy, c5) ? "true" : "false");
            printf("original: %s\n", strcmp(input, inputcpy)==0 ? "true" : "false");
            break;
        case -6:
            printf("mystrstr\n");
            compC = mystrstr("abcdedf", "ed");
            compS = strstr("abcdedf", "ed");
            printf("%s\n", *compC == *compS ? "true" : "false");
            break;
        case 6:
            printf("mystrstr\n");
            scanf("%s", input);
            sscanf(input, "%s", inputcpy);
            char c6[1000];
            scanf(" %s", c6);
            compC = mystrstr(input, c6);
            compS = strstr(inputcpy, c6);
            for (size_t i = 0; i < strlen(compC); i++)
            {
                printf("%d", compC[i] == compS[i]);
                printf("\n");
            }
            for (size_t i = 0; i < strlen(input); i++)
            {
                printf("%d", compC[i] == compS[i]);
            }
            printf("\n");

            break;

        case -7:
            printf("mystrtok\n");
            printf("%s\n",strcmp( mystrtok("abcdedf", "ed") ,strtok("abcdedf", "ed"))==0 ? "true" : "false");
            break;
        case 7:
            printf("mystrtok\n");
            scanf("%s", input);
            sscanf(input, "%s", inputcpy);
            char c7[1000];
            scanf("%s", c7);
            compC = mystrtok(input, c7);
            compS = strtok(inputcpy, c7);

            for (size_t i = 0; i < strlen(compC); i++)
            {
                printf("%d", compC[i] == compS[i]);
            }
            printf("\n");
            for (size_t i = 0; i < strlen(input); i++)
            {
                printf("%d", compC[i] == compS[i]);
            }
            printf("\n");

            break;
        default:
            break;
        }
    }
}