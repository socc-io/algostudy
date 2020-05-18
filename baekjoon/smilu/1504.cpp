#include <bits/stdc++.h>
using namespace std;

const int L_INF = 0x7fffffff;

struct edge {
  int v, w;
  edge() {}
  edge(int v, int w): v(v), w(w) {}
};

int n, m;
vector<edge> adj[801];

vector<int> dijkstra(int src) {
  vector<int> dist(n+1, L_INF);
  vector<bool> visit(n+1, false);
  priority_queue<pair<int,int>> q;
  dist[src] = 0;
  q.push({0, src});
  while (!q.empty()) {
    auto up = q.top();
    q.pop();
    int ud = -up.first;
    int u = up.second;
    if (visit[u]) continue;
    visit[u] = true;
    for (auto e: adj[u]) {
      int v = e.v, vd = ud + e.w;
      if (vd < dist[v]) {
        dist[v] = vd;
        q.push({-vd, v});
      }
    }
  }
  return dist;
}

int add(int a, int b) {
  if (a == L_INF || b == L_INF) return L_INF;
  return a + b;
}

int main(void)
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    int a, b, w;
    scanf("%d%d%d", &a, &b, &w);
    adj[a].emplace_back(b, w);
    adj[b].emplace_back(a, w);
  }
  int v1, v2;
  scanf("%d%d", &v1, &v2);
  vector<int> dist_1 = dijkstra(1);
  vector<int> dist_v1 = dijkstra(v1);
  vector<int> dist_v2 = dijkstra(v2);
  vector<int> dist_n = dijkstra(n);
  int d1 = add(add(dist_1[v1], dist_v1[v2]), dist_v2[n]);
  int d2 = add(add(dist_1[v2], dist_v2[v1]), dist_v1[n]);
  int ans = min(d1, d2);
  printf("%d\n", ans == L_INF ? -1 : ans);
}
