#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct edge {
  int v;
  ll w;
  edge() {}
  edge(int v, ll w): v(v), w(w) {}
};

int n, m;
vector<edge> adj[501];
ll dist[501];
bool in_queue[501];
int visit[501];

bool spfa(int src) {
  memset(dist, 0x3f, sizeof(dist));
  memset(in_queue, 0x00, sizeof(in_queue));
  memset(visit, 0x00, sizeof(visit));
  queue<int> q;
  q.push(src);
  dist[src] = 0;
  in_queue[src] = true;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    in_queue[u] = false;
    visit[u]++;
    if (visit[u] >= n+m) return true;
    for (auto e: adj[u]) {
      int v = e.v;
      ll vd = dist[u] + e.w;
      if (vd < dist[v]) {
        dist[v] = vd;
        if (!in_queue[v]) {
          in_queue[v] = true;
          q.push(v);
        }
      }
    }
  }
  return false;
}

int main(void)
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    int a, b;
    ll w;
    scanf("%d%d%lld", &a, &b, &w);
    adj[a].emplace_back(b, w);
  }
  if (spfa(1)) {
    puts("-1"); return 0;
  }
  for (int i = 2; i <= n; i++) printf("%lld\n", dist[i] == 0x3f3f3f3f3f3f3f3f ? -1 : dist[i]);
}
