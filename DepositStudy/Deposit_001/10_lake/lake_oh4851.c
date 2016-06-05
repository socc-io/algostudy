#include <stdio.h>

#define FINITE 255

typedef struct data {
    int row;
    int col;
} node;

int rowN, colM, top=0;
node stack[10001];
int grass[100][100] = {};

void push(int row, int col) {
    stack[++top].row = row;
    stack[top].col = col;
}

node pop() {
    return stack[top--];
}

void findNeighbor(int nr, int nc) {
    if ((0 <= nr && nr < rowN) && 
        (0 <= nc && nc < colM) && 
        (grass[nr][nc] == FINITE)) {
            push(nr, nc);
            grass[nr][nc] = -1;
    }
}

int main(void) {
    // your code goes here
    char input;
    int rowIdx, colIdx, count=0;
    node now;
    
    scanf("%d %d\n", &rowN, &colM);
    for (rowIdx=0; rowIdx<rowN; rowIdx++) {
        for (colIdx=0; colIdx<colM; colIdx++) {
            scanf("%c\n", &input);
            if (input == 'W') {
                grass[rowIdx][colIdx] = FINITE;
            }
        }
    }

    for (rowIdx=0; rowIdx<rowN; rowIdx++) {
        for (colIdx=0; colIdx<colM; colIdx++) {
            if (grass[rowIdx][colIdx] == FINITE) {
                count++;
                push(rowIdx, colIdx);
                while (1) {
                    if (top > 0) {
                        now = pop();

                        grass[now.row][now.col] = count;
                        findNeighbor(now.row, now.col+1);    //R
                        findNeighbor(now.row+1, now.col+1);  //RB
                        findNeighbor(now.row+1, now.col);    //B
                        findNeighbor(now.row+1, now.col-1);  //LB
                        findNeighbor(now.row, now.col-1);    //L
                        findNeighbor(now.row-1, now.col-1);  //LT
                        findNeighbor(now.row-1, now.col);    //T
                        findNeighbor(now.row-1, now.col+1);  //RT
                    }
                    else {
                        //STACK EMPTY
                        break;
                    }
                }
            }
        }
    }
    
    printf("%d", count);
    
    return 0;
}
