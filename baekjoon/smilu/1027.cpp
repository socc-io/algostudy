/*
 * author: smilu97
 * description:
 *  algorithm solving of https://www.acmicpc.net/problem/1027
 */

#include <cstdio>
#include <algorithm>
using namespace std;

#define EPS (1.0e-10)

typedef long long lld;

int N;
lld h[50];

lld ccw(lld x1, lld y1, lld x2, lld y2, lld x3, lld y3)
{
    return x1*y2+x2*y3+x3*y1 - y1*x2-y2*x3-y3*x1;
}

bool is_visible(int ai, int bi)
{
    if (ai > bi) swap(ai, bi);
    for (int mi = ai + 1; mi < bi; mi++)ㅔ {
        if (ccw(ai, h[ai], bi, h[bi], mi, h[mi]) >= 0) {
            return false;
        }
    }
    return true;
}

int count_visible(int idx)
{
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        if (i == idx) continue;
        cnt += is_visible(idx, i);
    }
    return cnt;
}

int main(void)
{
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%lld", h + i);
    }

    int maxcnt = 0;
    for (int i = 0; i < N; i++) {
        int cnt = count_visible(i);
        if (cnt > maxcnt) maxcnt = cnt;
    }
    printf("%d\n", maxcnt);
    
    return 0;
}
