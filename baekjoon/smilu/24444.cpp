#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> edges[100001];
int p[100001];
int r;

int max_p;

void bfs(int rt) {
    queue<int> q;
    p[rt] = ++max_p;
    q.push(rt);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v: edges[u]) {
            if (p[v] > 0) continue;
            p[v] = ++max_p;
            q.push(v);
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &r);
    for (int i = 0; i < m; i++) {
        int s, t; scanf("%d %d", &s, &t);
        edges[s].push_back(t);
        edges[t].push_back(s);
    }
    for (int i = 1; i <= n; i++) {
        sort(edges[i].begin(), edges[i].end());
    }
    bfs(r);
    for (int i = 1; i <= n; i++) {
        printf("%d\n", p[i]);
    }
}
