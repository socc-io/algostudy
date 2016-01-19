#include <stdio.h>
#include <stdlib.h>

int n, cnt; // 6 <= n <= 13

int checkImpossible(int br, int bc, int nr, int nc) {
    if (nc == bc) return 1;
    if (abs(nc - bc) == abs(nr - br)) return 1;
    return 0;
}

void copyHard(int *from, int *to) {
    int i;
    for (i=1; i<=n; i++) to[i] = from[i];
}

void findAnswer(int row, int *before) {
    int i, j, next[14];
    if (row > n) {
        if (cnt++ < 3) {
            for (i=1; i<=n; i++) printf("%d ", before[i]);
            printf("\n");
        }
        return;
    }
    for (i=1; i<=n; i++) {
        for (j=1; j<row; j++) {
            if(checkImpossible(j, before[j], row, i)) break;
        }
        if (j == row) {
            copyHard(before, next);
            next[row] = i;
            findAnswer(row + 1, next);
        }
    }
}

int main(void) {
    int i, queen[14];
    scanf("%d", &n);

    cnt = 0;

    findAnswer(1, queen);

    printf("%d\n", cnt);

    return 0;
}
