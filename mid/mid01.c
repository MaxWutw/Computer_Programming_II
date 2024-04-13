#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
int32_t matrix_multiply(int64_t *matrix1, int64_t *matrix2, int32_t *row1, int32_t *col1, int32_t *row2, int32_t *col2){
    int32_t rows1 = *row1;
    int32_t cols1 = *col1;
    int32_t rows2 = *row2;
    int32_t cols2 = *col2;
    int64_t result[rows1 * cols2];

    
    if (cols1 != rows2) {
        
        return -1;
    }

    for (int32_t i = 0; i < rows1; i++) {
        for (int32_t j = 0; j < cols2; j++) {
            result[i * cols2 + j] = 0;
            for (int32_t k = 0; k < cols1; k++) {
                result[i * cols2 + j] += matrix1[i * cols1 + k] * matrix2[k * cols2 + j];
            }
        }
    }

    for (int32_t i = 0; i < rows1; i++) {
        for (int32_t j = 0; j < cols2; j++) {
            matrix1[i * cols2 + j] = result[i * cols2 + j];
        }
    }

    *row1 = rows1;
    *col1 = cols2;
    // printf("\nrow col : %d %d\n", *row1, *col1);
    return 0;
}

int main(){
    // freopen("test.in", "r", stdin);
    int32_t inp = 1;
    char str[1200];
    int64_t matrix[500 * 500];
    int64_t result[500 * 500];
    int32_t res_row = 0, res_col = 0;
    while(1){
        fprintf(stdout, "%d matrix: ", inp);
        fgets(str, 1024, stdin);
        if(strcmp(str, "end\n") == 0 || strcmp(str, "end") == 0){
            inp--;
            break;
        }
        // parse
        int32_t row = 0;
        for(int32_t i = 0;i < strlen(str) - 1;i++){
            if(str[i] == '[') row++;
        }
        row -= 1;
        char *token = strtok((char *)str, "[,] ");
        int32_t idx = 0;
        while(token != NULL){
            // printf("%s\n", token);
            matrix[idx] = atoi(token);
            idx++;
            token = strtok(NULL, "[,] \n");
        }
        int32_t col = idx / row;
        if(inp == 1){
            res_row = row;
            res_col = col;
            for(int32_t i = 0;i < row;i++){
                for(int32_t j = 0;j < col;j++){
                    result[i * col + j] = matrix[i * col + j];
                }
            }
        }
        else{
            int32_t ret = matrix_multiply(result, matrix, &res_row, &res_col, &row, &col);
            if(ret == -1){
                fprintf(stdout, "Multiplication Fails\n");
                return 0;
            }
        }
        // printf("\n========================\n");
        // printf("%d %d\n", res_row, res_col);
        // printf("%d %d\n", row, col);
        // printf("\n========================\n");
        // for(int32_t i = 0;i < row;i++){
        //     for(int32_t j = 0;j < col;j++){
        //         printf("%d ", matrix[i * col + j]);
        //     }
        //     printf("\n");
        // }
        inp++;
    }
    fprintf(stdout, "Result: [");
    for(int32_t i = 0;i < res_row;i++){
        fprintf(stdout, "[");
        for(int32_t j = 0;j < res_col;j++){
            fprintf(stdout, "%d", result[i * res_col + j]);
            if(j != res_col - 1) fprintf(stdout, " ,");
        }
        fprintf(stdout, "]");
        if(i != res_row - 1) fprintf(stdout, " ,");
    }
    fprintf(stdout, "]\n");
    // for(int32_t r = 0;r < inp;r++){
        
    // }

    return 0;
}