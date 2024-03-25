#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "Hello, World! This is a test string.";
    char *token;

    // 使用 strtok() 分割字串
    token = strtok(str, " ,.!"); // 第一個參數是要分割的字串，第二個參數是分隔符
    printf("%s\n", token);
    // 依序取出分割後的 token
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, " ,.!"); // 使用 NULL 可以從上次停下的地方繼續分割
    }

    return 0;
}
