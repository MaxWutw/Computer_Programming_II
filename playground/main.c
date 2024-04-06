#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hex_to_int(const char *hex) {
    int value = 0;
    sscanf(hex, "%x", &value);
    printf("%d\n", value);
    return value;
}

int main() {
    char hex_string[] = "&Hffaaff"; // 输入的十六进制字符串
    int color_value = hex_to_int(hex_string + 2); // 跳过"&H"前缀

    // 提取颜色的红、绿、蓝分量
    int red = (color_value >> 16) & 0xFF;
    int green = (color_value >> 8) & 0xFF;
    int blue = color_value & 0xFF;

    // 使用ASCII转义序列在终端中显示颜色
    printf("\033[38;2;%d;%d;%dm", red, green, blue);
    printf("This text is colored!\n");
    printf("\033[0m"); // 恢复终端默认颜色

    return 0;
}
