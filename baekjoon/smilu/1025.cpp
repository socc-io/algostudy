/*
 * author: smilu97
 * description:
 *   algorithm solving of https://www.acmicpc.net/problem/1025
 */

#include <cstdio>
#include <cmath>

int N, M;
char tile[10][10];

bool is_square(int val)
{
    int s = (int) sqrt(val);
    for (int i = s - 2; i <= s + 2; i++) {
        if (i * i == val) return true;
    }
    return false;
}

bool inbound(int x, int y)
{
    return 0 <= x && x < N && 0 <= y && y < M;
}

int check(int x, int y)
{
    int max = -1;
    for (int dx = -N; dx < N; dx++) {
        for (int dy = -M; dy < M; dy++) {
            if (dx == 0 && dy == 0) continue;
            int cur = 0;
            for (int cx = x, cy = y;
                inbound(cx, cy);
                cx += dx, cy += dy) {
                cur = cur * 10 + tile[cx][cy];
                if (cur > max && is_square(cur)) max = cur;
            }
        }
    }
    return max;
}

int main(void)
{
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%s", tile[i]);
        for (int j = 0; j < M; j++) {
            tile[i][j] -= '0';
        }
    }
    
    int max = -1;
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            int val = check(x, y);
            if (val > max) max = val;
        }
    }
    printf("%d\n", max);

    return 0;
}