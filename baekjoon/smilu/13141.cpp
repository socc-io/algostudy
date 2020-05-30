#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;
typedef pair<pair<int, int>, int> pii;

const int MAX_N = 202;

struct Edge {
  int v, w;
  Edge() {}
  Edge(int v, int w): v(v), w(w) {}
};

int n, m;
vector<Edge> adj[MAX_N];
vector<pii> edges;

vector<int> dijkstra(int src) {
  vector<int> dst(n+1, 0x3f3f3f3f);
  vector<bool> vis(n+1, false);
  priority_queue<pi, vector<pi>, greater<pi>> q;
  dst[src] = 0;
  q.push({0, src});
  while (!q.empty()) {
    auto t = q.top(); q.pop();
    int u = t.second, ud = t.first;
    if (vis[u]) continue;
    vis[u] = true;
    for (auto e: adj[u]) {
      int v = e.v, w = e.w;
      int vd = ud + w;
      if (vd < dst[v]) {
        dst[v] = vd;
        q.push({vd, v});
      }
    }
  }
  return dst;
}

int main() {
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int a, b, w; cin >> a >> b >> w;
    w <<= 1;
    adj[a].push_back(Edge(b, w));
    adj[b].push_back(Edge(a, w));
    edges.push_back({{a, b}, w});
  }
  int ans = 0x3f3f3f3f;
  for (int i = 1; i <= n; i++) {
    vector<int> dst = dijkstra(i);
    int mt = dst[1];
    for (int j = 2; j <= n; j++) {
      mt = max(mt, dst[j]);
    }
    for (auto e: edges) {
      int a = e.first.first, b = e.first.second;
      int w = e.second;
      int t;
      a = dst[a], b = dst[b];
      if (b > a+w) t = a+w;
      else t = (a+b+w)/2;
      mt = max(mt, t);
    }
    ans = min(ans, mt);
  }
  double tmp = ans;
  tmp /= 2;
  printf("%.1lf\n", tmp);
}
