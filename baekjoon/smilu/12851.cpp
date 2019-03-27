/*
 * author: smilu97
 * description:
 *  algorithm solving of https://www.acmicpc.net/problem/12851
 */

#include <cstdio>
#include <queue>
using namespace std;

#define MAX 200000  // log2(MAX) ~= 16.xx
#define INF 10000000

int N, K;
int c[MAX + 1];
int d[MAX + 1];

int main(void)
{
    scanf("%d%d", &N, &K);

    c[N] = 1;
    queue<int> q;
    q.push(N);
    while(!q.empty()) {
        int u = q.front();
        q.pop();

        // printf("debug: visit %d(c: %d, d:, %d)\n", u, c[u], d[u]);

        auto visit = [&](int v) {
            if (v >= K * 2 || v > MAX) return;
            if (v < 0) return;
            if (c[v] == 0) {
                q.push(v);
                d[v] = d[u] + 1;
                c[v] = c[u];
            } else {
                if (d[v] == d[u] + 1) {
                    c[v] += c[u];
                }
            }
        };

        visit(u - 1);
        visit(u + 1);
        visit(u << 1);
    }

    printf("%d\n%d\n", d[K], c[K]);

    return 0;
}
