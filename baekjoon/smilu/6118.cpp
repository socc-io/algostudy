/*
 * author: smilu97
 * description:
 *  algorithm solving of https://www.acmicpc.net/problem/6118
 */

#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

#define MAXN 20000
#define MAXM 50000

int N, M;
vector<int> con[MAXN];  // contain connetion from [i]
int dist[MAXN];  // distance from spot[0]

int main(void)
{
    int tmp_a, tmp_b;

    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; i++) {
        scanf("%d%d", &tmp_a, &tmp_b);
        --tmp_a; --tmp_b;
        con[tmp_a].push_back(tmp_b);
        con[tmp_b].push_back(tmp_a);
    }

    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        // printf("debug: popped %d\n", u + 1);
        for (auto it = con[u].begin(); it != con[u].end(); ++it) {
            int v = *it;
            if (dist[v] != 0 || v == 0) continue;
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }

    int max_dist = -1;
    int same_cnt = 0;
    int max_idx = -1;
    for (int i = 0; i < N; i++) {
        if (max_dist < dist[i]) {
            max_dist = dist[i];
            same_cnt = 1;
            max_idx = i;
        } else if (max_dist == dist[i]) {
            same_cnt++;
        }
    }

    printf("%d %d %d\n", max_idx + 1, max_dist, same_cnt);

    return 0;
}
