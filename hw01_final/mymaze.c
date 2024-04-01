#include "mymaze.h"

int32_t find_min_path( const sRoom *pMaze, const uint8_t row, const uint8_t col, sPath *pMinPath ){
    uint8_t tmp = 202;
    uint8_t base = 0x03;
    // printf("%d\n", pMaze[0].doors >> 4 & base);
    // for(int32_t i = 3;i >= 0;i--){
    //     printf("%d\n", (tmp >> (i << 1) & base));
    // }
    // for(int32_t i = 0;i < row;i++){
    //     for(int32_t j = 0;j < col;j++){
    //         // for(int32_t i = 3;i >= 0;i--){
    //         //     // printf("%d\n", (tmp >> (i << 1) & base));
    //         //     printf("%d ")
    //         // }
    //         // printf("%d ", pMaze[i * col + j].cost);
    //         printf("%d ", (pMaze + (i * col + j))->cost);
    //     }
    //     printf("\n");
    // }
    sPath shortest, travel;
    shortest.length = 0;
    shortest.cost = 4294967294;
    shortest.pPath = (sPoint *)malloc(sizeof(sPoint) * row * col);

    travel.cost = 0;
    travel.length = 0;
    travel.pPath = (sPoint *)malloc(sizeof(sPoint) * row * col + sizeof(sPoint));
    int8_t *visited;
    visited = (int8_t *)calloc(row * col, sizeof(int8_t));
    // for(int32_t i = 0;i < row * col;i++) visited[i] = 0;
    dfs(pMaze, 0, 0, row, col, &shortest, &travel, visited);
    // printf("length: %d cost %d\n", shortest.length, shortest.cost);
    if(shortest.length == 0){
        free(travel.pPath);
        free(shortest.pPath);
        free(visited);
        return 0;
    }
    pMinPath->pPath = (sPoint*)malloc(sizeof(sPath) * shortest.length);
    pMinPath->cost = shortest.cost;
    pMinPath->length = shortest.length;
    for(int32_t i = 0;i < shortest.length;i++){
        (pMinPath->pPath + i)->row = (shortest.pPath + i)->row;
        (pMinPath->pPath + i)->col = (shortest.pPath + i)->col;
    }
    // for(int32_t i = 0;i < shortest.length;i++){
    //     printf("row: %d  col: %d\n", (pMinPath->pPath + i)->row, (pMinPath->pPath + i)->col);
    // }
    // printf("\n");
    free(travel.pPath);
    free(shortest.pPath);
    free(visited);
    return 1;
}

void dfs(const sRoom *pMaze, uint8_t x, uint8_t y, const uint8_t row, const uint8_t col, sPath *shortest, sPath *travel, int8_t *visited){
    // printf("x: %d y: %d\n", x, y);
    int32_t dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
    *(visited + (x * col) + y) = 1;
    if(x == row - 1 && y == col - 1){
        // printf("dafdasfsa");
        (travel->pPath + travel->length)->row = x;
        (travel->pPath + travel->length)->col = y;
        travel->length += 1;
        travel->cost += (pMaze + (x * col + y))->cost;
        if(travel->cost < shortest->cost){
            shortest->length = travel->length;
            shortest->cost = travel->cost;
            for(int32_t i = 0;i < travel->length;i++){
                (shortest->pPath + i)->row = (travel->pPath + i)->row;
                (shortest->pPath + i)->col = (travel->pPath + i)->col;
            }
        }
        (travel->pPath + travel->length)->row = 0;
        (travel->pPath + travel->length)->col = 0;
        travel->length -= 1;
        travel->cost -= (pMaze + (x * col + y))->cost;
        return;
    }
    for(int32_t i = 0;i < 4;i++){
        if(x + dx[i] >= 0 && x + dx[i] < row && y + dy[i] >= 0 && y + dy[i] < col){
            uint8_t tmp = (pMaze + (((x + dx[i]) * col) + y + dy[i]))->doors;
            // printf("dx: %d dy: %d\n", dx[i], dy[i]);
            uint8_t base = 0x03;
            if(dx[i] == -1){ // up
                if(*(visited + ((x + dx[i]) * col) + (y + dy[i])) == 0 && ((pMaze + (x * col + y))->doors >> 6 & base) == (tmp >> 2 & base)){
                    (travel->pPath + travel->length)->row = x;
                    (travel->pPath + travel->length)->col = y;
                    travel->length += 1;
                    travel->cost += (pMaze + (x * col + y))->cost;
                    dfs(pMaze, x + dx[i], y + dy[i], row, col, shortest, travel, visited);
                    (travel->pPath + travel->length)->row = 0;
                    (travel->pPath + travel->length)->col = 0;
                    travel->length -= 1;
                    travel->cost -= (pMaze + (x * col + y))->cost;
                    *(visited + ((x + dx[i]) * col) + (y + dy[i])) = 0;
                }
            }
            else if(dx[i] == 1){ // down
                // printf("%d\n", (pMaze + (x * col + y))->cost);
                if(*(visited + ((x + dx[i]) * col) + (y + dy[i])) == 0 && ((pMaze + (x * col + y))->doors >> 2 & base) == (tmp >> 6 & base)){
                    // printf("fdsafdsf");
                    (travel->pPath + travel->length)->row = x;
                    (travel->pPath + travel->length)->col = y;
                    travel->length += 1;
                    travel->cost += (pMaze + (x * col + y))->cost;
                    // printf("x + dx: %d y + dy: %d\n", x + dx[i], y + dy[i]);
                    dfs(pMaze, x + dx[i], y + dy[i], row, col, shortest, travel, visited);
                    (travel->pPath + travel->length)->row = 0;
                    (travel->pPath + travel->length)->col = 0;
                    travel->length -= 1;
                    travel->cost -= (pMaze + (x * col + y))->cost;
                    *(visited + ((x + dx[i]) * col) + (y + dy[i])) = 0;
                }
            }
            else if(dy[i] == 1){ // right
                if(*(visited + ((x + dx[i]) * col) + (y + dy[i])) == 0 && ((pMaze + (x * col + y))->doors >> 4 & base) == (tmp & base)){
                    (travel->pPath + travel->length)->row = x;
                    (travel->pPath + travel->length)->col = y;
                    travel->length += 1;
                    travel->cost += (pMaze + (x * col + y))->cost;
                    dfs(pMaze, x + dx[i], y + dy[i], row, col, shortest, travel, visited);
                    (travel->pPath + travel->length)->row = 0;
                    (travel->pPath + travel->length)->col = 0;
                    travel->length -= 1;
                    travel->cost -= (pMaze + (x * col + y))->cost;
                    *(visited + ((x + dx[i]) * col) + (y + dy[i])) = 0;
                }
            }
            else if(dy[i] == -1){ // left
                if(*(visited + ((x + dx[i]) * col) + (y + dy[i])) == 0 && ((pMaze + (x * col + y))->doors & base) == (tmp >> 4 & base)){
                    (travel->pPath + travel->length)->row = x;
                    (travel->pPath + travel->length)->col = y;
                    travel->length += 1;
                    travel->cost += (pMaze + (x * col + y))->cost;
                    dfs(pMaze, x + dx[i], y + dy[i], row, col, shortest, travel, visited);
                    (travel->pPath + travel->length)->row = 0;
                    (travel->pPath + travel->length)->col = 0;
                    travel->length -= 1;
                    travel->cost -= (pMaze + (x * col + y))->cost;
                    *(visited + ((x + dx[i]) * col) + (y + dy[i])) = 0;
                }
            }
        }
    }
}