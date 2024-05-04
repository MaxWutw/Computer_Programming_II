// #include <stdio.h>
// #include <stdint.h>
// #include <stdlib.h>
// int main(){
// 	char *newfile = "output.txt";
// 	FILE *pBinary;
// 	if((pBinary = fopen(newfile, "w+b")) == NULL){
//         fprintf(stderr, "Error: Unable to open file for reading or writing\n");
//         return 0;
//     }
// 	int8_t data = 4;
//     int8_t rda = 0;
//     fread(&rda, 1, 1, pBinary);
//     fwrite(&data, 1, 1, pBinary);
//     printf("%u\n", rda);

// 	return 0;
// }

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main() {
    char *newfile = "output.txt";
    FILE *pBinary;

    if ((pBinary = fopen(newfile, "rb")) == NULL) {
        fprintf(stderr, "Error: Unable to open file for reading or writing\n");
        return 1;
    }

    int8_t data = 4;
    int8_t rda = 0;

    // 寫入 data 到檔案中
    // fwrite(&data, 1, 1, pBinary);

    // // 移動文件指標到開頭
    // fseek(pBinary, 0, SEEK_SET);

    // 從檔案中讀取資料到 rda
    fread(&rda, 1, 1, pBinary);

    // // 輸出 rda 的值
    printf("%d\n", rda);

    // 關閉檔案
    fclose(pBinary);

    return 0;
}
