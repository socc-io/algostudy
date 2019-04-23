/*
 * author: smilu97
 * description:
 *  algorithm solving of https://www.acmicpc.net/problem/1023
 *  ref: http://wookje.dance/2018/11/14/boj-1023/
 */

#include <cstdio>
#include <cstring>

typedef long long lld;

const lld INF = 0x3f3f3f3f3f3f3f3f;
int N;
lld K, dp[55][105][2];

lld getdp(int depth, int point, int neg)
{
    if (depth == N) return neg || point != 50;
    lld &ret = dp[depth][point][neg];
    if (ret != INF) return ret;
    return ret = getdp(depth + 1, point - 1, neg || point <= 50)
        + getdp(depth + 1, point + 1, neg);
}

void solve(int depth, int point, int neg)
{
    if (depth == N) return;
    if (dp[depth + 1][point + 1][neg] >= K) {
        if (depth == N - 1 && K == 2) putchar(')');
        else putchar('(');
        solve(depth + 1, point + 1, neg);
    } else {
        putchar(')');
        K -= dp[depth + 1][point + 1][neg];
        solve(depth + 1, point - 1, neg || point <= 50);
    }
}

int main(void)
{
    scanf("%d%lld", &N, &K); K++;

    memset(dp, 0x3f, sizeof(dp));
    getdp(0, 50, 0);

    if (dp[0][50][0] < K) {
        return !puts("-1");
    }
    solve(0, 50, 0);

    return 0;
}