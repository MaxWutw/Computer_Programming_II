#include <stdio.h>
#include <stdint.h>
void test(char *str){

}
int main(){
    char str[100];
    for(int i = 0;i < 20;i++) str[i] = 'a' + i;
    str[20] = 'z';
    printf("%s\n", str);
    printf("%d\n", str[21]);
    
    return 0;
}