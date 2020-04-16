#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

#define INF 0x7FFFFFFF

struct edge {
  int v, t;
  edge() {}
  edge(int v, int t): v(v), t(t) {}
};

int n, m, w;
vector<edge> edges[500];
bool visited[500];

bool spfa(int start) {
  queue<int> q;
  vector<bool> in_queue(n, false);
  vector<int> d(n, INF);
  vector<int> par(n, -1);
  vector<int> cnt(n, 0);

  q.push(start);
  in_queue[start] = true;
  d[start] = 0;
  visited[start] = true;

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    in_queue[u] = false;
    int ud = d[u];
    for (auto &e: edges[u]) {
      int v = e.v;
      int vd = ud + e.t;
      visited[v] = true;
      if (vd >= d[v]) continue;
      d[v] = vd;
      if (par[v] == u) {
        cnt[v]++;
        if (cnt[v] >= 10) return true;
      } else {
        cnt[v] = 0;
        par[v] = u;
      }
      if (!in_queue[v]) {
        q.push(v);
        in_queue[v] = true;
      }
    }
  }

  return false;
}

void solve() {
  scanf("%d%d%d", &n, &m, &w);
  for (int i = 0; i < n; i++) {
    edges[i].clear();
    visited[i] = false;
  }
  for (int i = 0; i < m; i++) {
    int s, e, t;
    scanf("%d%d%d", &s, &e, &t);
    --s; --e;
    edges[s].push_back(edge(e, t));
    edges[e].push_back(edge(s, t));
  }
  for (int i = 0; i < w; i++) {
    int s, e, t;
    scanf("%d%d%d", &s, &e, &t);
    --s; --e;
    edges[s].push_back(edge(e, -t));
  }
  bool ans = false;
  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      bool res = spfa(i);
      // printf("start: %d, res: %d\n", i, res);
      if (res) {
        ans = true;
        break;
      }
    }
  }
  puts(ans ? "YES" : "NO");
}

int main(void)
{
  int t; scanf("%d", &t);
  while (t--) solve();
}
