#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f;

int f[444][444];
vector<int> adj[444];
int n, m, sv, ev;
int lev[444];
int wi[444];

void add_edge(int u, int v, int w = inf) {
  adj[u].push_back(v); adj[v].push_back(u);
  f[u][v] = w;
}

int set_level() {
  memset(lev, 0, sizeof(lev));
  queue<int> q; q.push(sv);
  lev[sv] = 1;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v: adj[u]) {
      if (f[u][v] <= 0) continue;
      if (lev[v]) continue;
      lev[v] = lev[u] + 1;
      q.push(v);
    }
  }
  return lev[ev];
}

int dinic_dfs(int u, int mf) {
  if (u == ev) return mf;
  for (int &i = wi[u]; i < adj[u].size(); i++) {
    int v = adj[u][i];
    if (lev[v] != lev[u] + 1) continue;
    if (f[u][v] <= 0) continue;
    int nf = dinic_dfs(v, min(mf, f[u][v]));
    if (nf <= 0) continue;
    f[u][v] -= nf;
    f[v][u] += nf;
    return nf;
  }
  return 0;
}

void dinic() {
  while (set_level()) {
    memset(wi, 0, sizeof(wi));
    while (dinic_dfs(sv, inf));
  }
}

int main(void)
{
  scanf("%d%d%d%d", &n, &m, &sv, &ev);
  ev += n;
  for (int i = 1; i <= n; i++) {
    int t; scanf("%d", &t);
    add_edge(i, i+n, t);
  }
  for (int i = 0; i < m; i++) {
    int a, b; scanf("%d%d", &a, &b);
    add_edge(a+n, b);
    add_edge(b+n, a);
  }
  dinic();
  set_level();
  for (int i = 1; i <= n; i++) if (lev[i] && !lev[i+n]) {
    printf("%d ", i);
  } puts("");
}
