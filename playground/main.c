#include <stdio.h>

int main() {
    float speed;
    int result;

    // 尝试从标准输入中读取一个浮点数值
    result = fscanf(stdin, "%f", &speed);

    // 检查读取结果
    if (result != 1) {
        printf("无法读取浮点数值\n");
        return 1;
    }

    // 打印读取的值
    printf("读取的浮点数值为: %f\n", speed);

    return 0;
}