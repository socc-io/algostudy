#include <cstdio>
#include <vector>
using namespace std;

int n, q, r;
int par[100001][20];
int lev[100001];
int wei[100001];
vector<int> adj[100001];

void build_tree(int u, int p) {
  lev[u] = lev[p] + 1;
  par[u][0] = p;
  for (int i = 1; i < 20; i++) {
    par[u][i] = par[par[u][i-1]][i-1];
  }
  wei[u] = 1;
  for (int v: adj[u]) {
    if (v == p) continue;
    build_tree(v, u);
    wei[u] += wei[v];
  }
}

int get_ancestor(int a, int lv) {
  for (int i = 19; i >= 0; i--) {
    if (lev[a] - (1<<i) < lv) continue;
    a = par[a][i];
  }
  return a;
}

bool is_ancestor(int a, int b) {
  return get_ancestor(b, lev[a]) == a;
}

int weight(int u) {
  if (u == r) return n;
  if (lev[r] > lev[u] && is_ancestor(u, r)) {
    int ret = n;
    for (int v: adj[u]) {
      if (v == par[u][0]) continue;
      if (!is_ancestor(v, r)) continue;
      ret -= wei[v];
    }
    return ret;
  }
  return wei[u];
}

void solve() {
  scanf("%d%d%d", &n, &q, &r);
  for (int i = 0; i <= n; i++) adj[i].clear();
  for (int i = 1; i < n; i++) {
    int a, b; scanf("%d%d", &a, &b);
    adj[a].emplace_back(b);
    adj[b].emplace_back(a);
  }
  build_tree(1, 0);
  for (int i = 0; i < q; i++) {
    int a, b; scanf("%d%d", &a, &b);
    if (a == 0) r = b;
    else {
      printf("%d\n", weight(b));
    }
  }
}

int main(void)
{
  int t; scanf("%d", &t);
  for (int i = 1; i <= t; i++) {
    printf("Case #%d:\n", i);
    solve();
  }
}
