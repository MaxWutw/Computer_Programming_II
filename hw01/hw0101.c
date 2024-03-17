#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mystring.h"
int main(){
    // const char *str1 = "This is a c-style string";
    // const char *str2 = "c-style";
    // int siz = mystrpbrk(str1, str2);
    // printf("%d\n", siz);
    // char *str = mystrstr(str1, str2);
    // printf("%s\n", str);
    char str[] = "Hello world, nice to meet you";
    const char* d = "  ,";
    char *p;
    p = mystrtok(str, d);
    // char *str1 = "hello";
    // char *str2 = str1;
    // str2 = ";";
    // printf("%s\n", str1);
    // printf("%s\n", p);
    while (p != NULL) {
        printf("%s\n", p);
        p = mystrtok(NULL, d);		   
    }

    return 0;
}
// #include <stdio.h>
// #include <string.h>
// int main()
// {
//     int len;
//     // initializing strings
//     const char *s1 = "abcdefg book";
//     const char *s2 = "c";
//     // using strcspn() to compute initial chars
//     // before 1st matching chars.
//     // returns 3
//     len = strcspn(s1, s2);
//     printf("length of string that characters not present in s2: %d\n", len);
//     return 0;
// }