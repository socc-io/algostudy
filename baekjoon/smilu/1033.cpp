/*
 * author: smilu97
 * description:
 *   algorithm solving of https://www.acmicpc.net/problem/1033
 */

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long lld;

struct conn {
    int idx, p, q;
};

lld gcd(lld a, lld b)
{
    if (a < b) swap(a, b);
    while (b) {
        lld tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

int N;
vector<conn> con[10];
bool visit[10];
lld val[10];

void propagate(int idx)
{
    visit[idx] = true;
    for(auto tcon: con[idx]) {
        int bi = tcon.idx;
        if (visit[bi]) continue;
        int p = tcon.p;
        int q = tcon.q;
        lld m = p / gcd(val[idx], p);
        for (int i = 0; i < N; i++) {
            if (visit[i]) val[i] *= m;
        }
        val[bi] = val[idx] / p * q;
        propagate(bi);
    }
}

int main(void)
{
    conn tcon;

    scanf("%d", &N);
    for (int i = 0; i < N - 1; i++) {
        int ai, bi, p, q;
        scanf("%d%d%d%d", &ai, &bi, &p, &q);
        tcon.idx = bi;
        tcon.p = p;
        tcon.q = q;
        con[ai].push_back(tcon);
        tcon.idx = ai;
        tcon.p = q;
        tcon.q = p;
        con[bi].push_back(tcon);
    }
    
    val[0] = 1;
    propagate(0);

    lld g = val[0];
    for (int i = 1; i < N; i++) {
        g = gcd(g, val[i]);
    }

    for (int i = 0; i < N; i++) {
        printf("%lld ", val[i] / g);
    } puts("");

    return 0;
}