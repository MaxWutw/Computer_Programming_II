// #include <stdio.h>
// #include <stdlib.h>
// #include "mymaze.h"
// int main(){
//     sRoom pMaze[15];
//     sPath pMinPath;
//     pMinPath.pPath = NULL;
//     uint8_t row = 3, col = 4;
//     pMaze[0 * col + 0].cost = 1;
//     pMaze[0 * col + 0].doors = (uint8_t)0b01110101;

//     pMaze[0 * col + 1].cost = 7;
//     pMaze[0 * col + 1].doors = (uint8_t)0b11000011;

//     pMaze[0 * col + 2].cost = 2;
//     pMaze[0 * col + 2].doors = (uint8_t)0b11011100;

//     pMaze[0 * col + 3].cost = 8;
//     pMaze[0 * col + 3].doors = (uint8_t)0b11100101;

//     pMaze[1 * col + 0].cost = 2;
//     pMaze[1 * col + 0].doors = (uint8_t)0b00101111;

//     pMaze[1 * col + 1].cost = 5;
//     pMaze[1 * col + 1].doors = (uint8_t)0b10111100;

//     pMaze[1 * col + 2].cost = 10;
//     pMaze[1 * col + 2].doors = (uint8_t)0b01001010;

//     pMaze[1 * col + 3].cost = 2;
//     pMaze[1 * col + 3].doors = (uint8_t)0b01111001;

//     pMaze[2 * col + 0].cost = 9;
//     pMaze[2 * col + 0].doors = (uint8_t)0b00101100;

//     pMaze[2 * col + 1].cost = 15;
//     pMaze[2 * col + 1].doors = (uint8_t)0b01111011;

//     pMaze[2 * col + 2].cost = 7;
//     pMaze[2 * col + 2].doors = (uint8_t)0b01111010;

//     pMaze[2 * col + 3].cost = 3;
//     pMaze[2 * col + 3].doors = (uint8_t)0b10001101;

    
//     // printf("%d\n", pMaze[0].doors);
//     find_min_path(pMaze, row, col, &pMinPath);
//     free(pMinPath.pPath);

//     return 0;
// }

// #include "mymaze.h"
// int main()
// {   
//     freopen("test.in", "r", stdin);
//     uint8_t row = 0, col = 0;
//     scanf("%hhu", &row);
//     scanf("%hhu", &col);
//     sRoom inp[row][col];
//     for (uint8_t i = 0; i < row; i++)
//     {
//         for (uint8_t j = 0; j < col; j++)
//         {
//             scanf("%u", &inp[i][j].cost);
//             // input doors in four sides
//             uint8_t up, right, down, left;
//             scanf("%hhu %hhu %hhu %hhu", &up, &right, &down, &left);
//             inp[i][j].doors = (up << 6) | (right << 4) | (down << 2) | left;
//         }
//     }
//     sPath result;
//     printf("return: %d\n",find_min_path(inp,row,col,&result));
//     printf("cost:%d length:%d\n\n",result.cost,result.length);
//     for(uint32_t i=0;i<result.length;i++)
//     {
//         printf("%d %d\n",result.pPath[i].row,result.pPath[i].col);
//     }
//     free(result.pPath);
// }

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "mymaze.h"

// 迷宮1
sRoom maze1[5][5] = {
    {{1, 0b00010001}, {3, 0b00100001}, {3, 0b00100001}, {2, 0b00100010}, {1, 0b00100000}},
    {{1, 0b00000101}, {0, 0b00000000}, {0, 0b00000000}, {0, 0b00000000}, {1, 0b01000000}},
    {{1, 0b00010100}, {2, 0b01010000}, {1, 0b00010001}, {3, 0b00100001}, {1, 0b00100000}},
    {{1, 0b10000001}, {0, 0b00000000}, {0, 0b00000000}, {0, 0b00000000}, {1, 0b01000000}},
    {{1, 0b10000100}, {3, 0b01001000}, {2, 0b01001000}, {3, 0b01000100}, {2, 0b00000000}}
};

// 迷宮2
sRoom maze2[5][5] = {
    {{4, 0b00010001}, {1, 0b00100001}, {2, 0b00100001}, {2, 0b00100010}, {3, 0b00100000}},
    {{2, 0b00000101}, {3, 0b00000000}, {2, 0b00000000}, {1, 0b00000000}, {2, 0b01000000}},
    {{3, 0b00010100}, {1, 0b01010000}, {2, 0b00010001}, {2, 0b00100001}, {3, 0b00100000}},
    {{1, 0b10000001}, {2, 0b00000000}, {3, 0b00000000}, {2, 0b00000000}, {1, 0b01000000}},
    {{3, 0b10000100}, {1, 0b01001000}, {2, 0b01001000}, {4, 0b01000100}, {5, 0b00000000}}
};

// 迷宮3
sRoom maze3[5][5] = {
    {{2, 0b00010001}, {1, 0b00100001}, {3, 0b00100001}, {1, 0b00100010}, {2, 0b00100000}},
    {{1, 0b10000101}, {2, 0b00000000}, {1, 0b00000000}, {2, 0b00000000}, {1, 0b01000000}},
    {{3, 0b10010100}, {1, 0b01010000}, {2, 0b00010001}, {3, 0b00100001}, {2, 0b00100000}},
    {{1, 0b10000001}, {2, 0b00000000}, {3, 0b00000000}, {1, 0b00000000}, {3, 0b01000000}},
    {{2, 0b10000100}, {3, 0b01001000}, {1, 0b01001000}, {2, 0b01000100}, {4, 0b00000000}}
};

// 迷宮4
sRoom maze4[5][5] = {
    {{1, 0b00010001}, {1, 0b00100001}, {1, 0b00100001}, {1, 0b00100010}, {1, 0b00100000}},
    {{1, 0b10000101}, {1, 0b00000000}, {1, 0b00000000}, {1, 0b00000000}, {1, 0b01000000}},
    {{1, 0b10010100}, {1, 0b01010000}, {1, 0b00010001}, {1, 0b00100001}, {1, 0b00100000}},
    {{1, 0b10000001}, {1, 0b00000000}, {1, 0b00000000}, {1, 0b00000000}, {1, 0b01000000}},
    {{1, 0b10000100}, {1, 0b01001000}, {1, 0b01001000}, {1, 0b01000100}, {1, 0b01000000}}
};

// 無解情況迷宮5
sRoom maze5[3][4] = {
    {{1, 0b01110101}, {7, 0b11000011}, {2, 0b11011100}, {8, 0b11100101}},
    {{2, 0b00101111}, {5, 0b10111100}, {10, 0b01001010}, {2, 0b01111001}},
    {{9, 0b00101100}, {15, 0b01111011}, {7, 0b01111010}, {3, 0b10001101}},
};

int main() {
    int choice;
    printf("請選擇一個測試數據:\n");
    printf("1. 標準情況迷宮1\n");
    printf("2. 標準情況迷宮2\n");
    printf("3. 特殊情況迷宮3\n");
    printf("4. 特殊情況迷宮4\n");
    printf("5. 無解情況迷宮5\n");
    printf("6. 無解情況迷宮6\n");
    printf("7. 異常輸入迷宮7\n");
    printf("8. 異常輸入迷宮8\n");
    printf("請輸入你的選擇(1-8): ");
    scanf("%d", &choice);
    sPath minPath = {0, 0, NULL};
    int32_t result;
    switch (choice) {
        case 1:
            result = find_min_path((const sRoom *)maze1, 5, 5, &minPath);
        break;
        case 2:
            result = find_min_path((const sRoom *)maze2, 5, 5, &minPath);

            break;
        // 添加其他情況
        case 3:
            result = find_min_path((const sRoom *)maze3, 5, 5, &minPath);
            break;
        case 4:
            result = find_min_path((const sRoom *)maze4, 5, 5, &minPath);
            break;
        case 5:
            result = find_min_path((const sRoom *)maze5, 3, 4, &minPath);
            break;
        default:
            printf("無效的選擇。\n");
    }

    if (result == 1) {
        printf("找到最小成本路徑，成本為: %u\n", minPath.cost);
        // 可選：打印路徑詳情
    } else if (result == 0) {
        printf("沒有找到路徑。\n");
    } else {
        printf("輸入有誤。\n");
    }

    // 清理分配的路徑內存
    free(minPath.pPath);

    return 0;
}