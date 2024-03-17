#include <stdio.h>

// 函数用于将十进制数转换为任意进制数
void decimalToBase(int decimal, int base) {
    int quotient, remainder;
    int i = 0;
    char baseNumber[100];

    quotient = decimal;

    // 将十进制数转换为指定进制数
    while (quotient != 0) {
        remainder = quotient % base;

        // 将余数转换为指定进制的数字
        if (remainder < 10)
            baseNumber[i++] = remainder + '0'; // 如果是0-9，则直接加上 '0' 来转换为字符
        else
            baseNumber[i++] = remainder + 'A' - 10; // 如果是10以上的数，用 'A' - 10 来转换为字符
        
        quotient = quotient / base;
    }

    // 倒序打印出转换后的任意进制数
    printf("Equivalent base-%d value of decimal number %d: ", base, decimal);
    for (int j = i - 1; j >= 0; j--)
        printf("%c", baseNumber[j]);
    printf("\n");
}

int main() {
    int decimal, base;

    // 输入十进制数和目标进制
    printf("Enter a decimal number: ");
    scanf("%d", &decimal);
    printf("Enter the base to convert to: ");
    scanf("%d", &base);

    // 调用函数将十进制数转换为指定进制数
    decimalToBase(decimal, base);

    return 0;
}