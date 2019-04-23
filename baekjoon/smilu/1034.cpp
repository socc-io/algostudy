/*
 * author: smilu97
 * description:
 *   algorithm solving of https://www.acmicpc.net/problem/1034
 */

#include <cstdio>
#include <map>
using namespace std;

typedef long long lld;

int N, M, K;
lld lamp[50];
int req[50];

int main(void)
{
    lld tmp;

    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%1lld", &tmp);
            lamp[i] |= tmp << j;
            req[i] += 1 - tmp;
        }
    }
    scanf("%d", &K);

    map<lld, int> cnt;
    for (int i = 0; i < N; i++) {
        if (req[i] > K) continue;
        if ((K - req[i]) & 1) continue;
        cnt[lamp[i]]++;
    }

    int res = 0;
    for (auto it = cnt.begin(); it != cnt.end(); ++it) {
        if (it->second > res) res = it->second;
    }
    
    printf("%d\n", res);

    return 0;
}