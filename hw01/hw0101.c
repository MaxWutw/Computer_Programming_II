#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mystring.h"
int main(){
    const char *str1 = "abcdefg book";
    const char *str2 = "cbe";
    int siz = mystrcspn(str1, str2);
    printf("%d\n", siz);

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