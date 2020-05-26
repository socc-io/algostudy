#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pi;

struct Edge {
  int v, w;
  Edge() {}
  Edge(int v, int w): v(v), w(w) {}
};

struct BackEdge {
  int u, r, w;
  BackEdge() {}
  BackEdge(int u, int r, int w): u(u), r(r), w(w) {}
};

int n, m;
int start, dest;
vector<Edge> adj[500];
vector<BackEdge> bdj[500];

void add_edge(int u, int v, int w) {
  adj[u].push_back(Edge(v, w));
  bdj[v].push_back(BackEdge(u, adj[u].size() - 1, w));
}

vector<int> dijkstra() {
  priority_queue<pi, vector<pi>, greater<pi>> q;
  vector<bool> vis(n);
  vector<int> dst(n, 0x3f3f3f3f);
  dst[start] = 0;
  q.push(make_pair(0, start));
  while (!q.empty()) {
    auto t = q.top(); q.pop();
    int u = t.second, ud = t.first;
    if (vis[u]) continue;
    vis[u] = true;
    for (auto e: adj[u]) {
      int v = e.v, w = e.w;
      if (w == 0) continue;
      int vd = ud + w;
      if (vd < dst[v]) {
        dst[v] = vd;
        q.push(make_pair(vd, v));
      }
    }
  }
  return dst;
}

void remove_shortest(const vector<int> &dst, int v) {
  for (auto &be: bdj[v]) {
    int u = be.u;
    if (dst[v] - be.w == dst[u]) {
      auto &e = adj[u][be.r];
      e.w = 0;
      be.w = 0;
      remove_shortest(dst, u);
    }
  }
}

int main(void)
{
  ios::sync_with_stdio(0); cin.tie(0);
  while (1) {
    cin >> n >> m;
    if (n == 0 && m == 0) break;
    for (int i = 0; i < n; i++) adj[i].clear();
    for (int i = 0; i < n; i++) bdj[i].clear();
    cin >> start >> dest;
    for (int i = 0; i < m; i++) {
      int a, b, w; cin >> a >> b >> w;
      add_edge(a, b, w);
    }
    auto dst = dijkstra();
    remove_shortest(dst, dest);
    auto dst2 = dijkstra();
    cout << (dst2[dest] == 0x3f3f3f3f ? -1 : dst2[dest]) << '\n';
  }
}
