/*
 * author: smilu97
 * description:
 *   algorithm solving of https://www.acmicpc.net/problem/1035
 */

#include <cstdio>

struct coord {
    int x, y;
};

char tile[5][5];
int dummy;  // 1byte overflow guard
coord p[5];
bool g[5];

void move(int idx, int to, int cost)
{
    
}

int center(int idx)
{
    g[idx] = true;
    for (int i = 0; i < 5; i++) {
        if (i == idx) continue;
        move(i, idx, 0);
    }
}

int main(void)
{
    int tmp;

    tmp = 0;
    for (int i = 0; i < 5; i++) {
        scanf("%s", tile[i]);
        for (int j = 0; j < 5; j++) {
            if (tile[i][j] == '*') {
                p[tmp].x = i;
                p[tmp++].y = j;
            }
        }
    }

    int res = 12345;
    for (int i = 0; i < 5; i++) {
        int val = center(i);
        if (val < res) res = val;
    }

    printf("%d\n", res);

    return 0;
}