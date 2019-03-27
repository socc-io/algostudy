/*
 * author: smilu97
 * description:
 *  problem solving of https://www.acmicpc.net/problem/1028
 */

#include <cstdio>

int R, C;
char tile[750][751];
int dur[750][750];  // dp up right
int ddr[750][750];  // dp down right

int min(int a, int b) { return a < b ? a : b; }

void init_dp()
{
    for (int i = 0; i < R; i++) {
        dur[i][C - 1] = tile[i][C - 1];
        ddr[i][C - 1] = tile[i][C - 1];
    }
    for (int i = 0; i < C; i++) {
        dur[0][i] = tile[0][i];
        ddr[R - 1][i] = tile[R - 1][i];
    }
    for (int i = 1; i < R; i++) {
        for (int j = C - 2; j >= 0; j--) {
            if (tile[i][j]) dur[i][j] = dur[i-1][j+1] + 1;
        }
    }
    for (int i = R - 2; i >= 0; i--) {
        for (int j = C - 2; j >= 0; j--) {
            if (tile[i][j]) ddr[i][j] = ddr[i+1][j+1] + 1;
        }
    }
}

int check_spot(int x, int y)
{
    int sz = R - x;
    sz = min(sz, x + 1);
    sz = min(sz, (C - y + 1) / 2);
    sz = min(sz, dur[x][y]);
    sz = min(sz, ddr[x][y]);
    for (; sz > 0; sz--) {
        if (ddr[x - sz + 1][y + sz - 1] < sz) continue;
        if (dur[x + sz - 1][y + sz - 1] < sz) continue;
        return sz;
    }
    return 0;
}

int main(void)
{
    // freopen("input.txt", "r", stdin);
    scanf("%d%d", &R, &C);
#ifndef ONLINE_JUDGE
    puts("\ntile:");
#endif
    for (int i = 0; i < R; i++) {
        scanf("%750s", (char*)(tile + i));
#ifndef ONLINE_JUDGE
        printf("  %s\n", tile[i]);
#endif
        for (int j = 0; j < C; j++) {
            tile[i][j] -= '0';
        }
    }

    init_dp();

#ifndef ONLINE_JUDGE
    puts("\ndur:");
    for (int i = 0; i < R; i++) {
        printf("  ");
        for (int j = 0; j < C; j++) {
            printf("%d", dur[i][j]);
        } puts("");
    }
    puts("\nddr:");
    for (int i = 0; i < R; i++) {
        printf("  ");
        for (int j = 0; j < C; j++) {
            printf("%d", ddr[i][j]);
        } puts("");
    }
#endif

    int maxsz = 0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            int sz = check_spot(i, j);
            if (sz > maxsz) maxsz = sz;
        }
    }
    printf("%d\n", maxsz);

    return 0;
}