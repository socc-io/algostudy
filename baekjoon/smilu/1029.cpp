/*
 * author: smilu97
 * description:
 *   problem solving of https://www.acmicpc.net/problem/1029
 */

#include <cstdio>

#ifndef ONLINE_JUDGE
#define DEBUG
#endif

int N;
char cost[15][15];
char dp[1<<15][15][10];

/*
 * @arguments
 *  s[in]: state
 *  a[in]: artist
 *  c[in]: cost
 *  d[in]: cost
 */
char f(int s, int a, int c, int d)
{
    char &ret = dp[s][a][c];
    if (ret) return ret;

    ret = d;
    for (int i = 0; i < N; i++) {
        if (s & (1<<i) || cost[a][i] < c) continue;
        int val = f(s | (1<<i), i, cost[a][i], d + 1);
        if (val > ret) ret = val;
    }

    return ret;
}

int main(void)
{
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%1s", cost[i] + j);
            cost[i][j] -= '0';
        }
    }

#ifdef DEBUG
    printf("N: %d\n", N);
    for (int i = 0; i < N; i++) {
        printf("  ");
        for (int j = 0; j < N; j++) {
            printf("%d", cost[i][j]);
        } puts(""); 
    } puts("");
#endif

#ifdef DEBUG
    printf("ans: ");
#endif
    printf("%d\n", f(1, 0, 0, 1));

    return 0;
}