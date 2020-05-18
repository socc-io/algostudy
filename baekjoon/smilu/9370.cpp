#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pi;

struct edge {
  int a, b, w;
  int v(int u) {
    return u == a ? b : a;
  }
  edge() {}
  edge(int a, int b, int w): a(a),b(b),w(w) {}
};

int n, m, t;
int s, g, h;
int tei;
vector<edge> edges;
vector<int> adj[2001];
int dist[2001];
bool visit[2001];

void dijkstra(int src) {
  memset(dist, 0x3f, sizeof(dist));
  memset(visit, 0x00, sizeof(visit));
  priority_queue<pi, vector<pi>, greater<pi>> q;
  dist[src] = 0;
  q.push({0, src});
  while (!q.empty()) {
    auto up = q.top(); q.pop();
    int ud = up.first;
    int u = up.second;
    if (visit[u]) continue;
    visit[u] = true;
    for (int ei: adj[u]) {
      auto e = edges[ei];
      int v = e.v(u), vd = ud + e.w;
      if (vd < dist[v]) {
        dist[v] = vd;
        q.push({vd, v});
      }
    }
  }
}

bool dfs_edges(int u) {
  visit[u] = true;
  for (int ei: adj[u]) {
    auto e = edges[ei];
    int v = e.v(u);
    if (dist[v] != dist[u] - e.w) continue;
    if (ei == tei) return true;
    if (!visit[v] && dfs_edges(v)) return true;
  }
  return false;
}

void solve() {
  scanf("%d%d%d%d%d%d", &n, &m, &t, &s, &g, &h);
  if (g > h) swap(g, h);
  edges.clear();
  for (int i = 0; i <= n; i++) adj[i].clear();
  for (int i = 0; i < m; i++) {
    int a, b, w; scanf("%d%d%d", &a, &b, &w);
    adj[a].push_back(edges.size());
    adj[b].push_back(edges.size());
    if (a == g && b == h) tei = edges.size();
    edges.emplace_back(a, b, w);
  }
  dijkstra(s);
  vector<int> ans;
  for (int i = 0; i < t; i++) {
    int tmp; scanf("%d", &tmp);
    memset(visit, 0x00, sizeof(visit));
    if (dfs_edges(tmp)) {
      ans.push_back(tmp);
    }
  }
  sort(ans.begin(), ans.end());
  for (int v: ans) printf("%d ", v); puts("");
}

int main(void)
{
  int T; scanf("%d", &T);
  while (T--) solve();
}
