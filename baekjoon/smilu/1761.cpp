#include <bits/stdc++.h>
using namespace std;

int n;
vector<pair<int,int>> adj[40001];
int lev[40001];
int dis[40001];
int par[40001][20];

void init_tree(int u, int p) {
  lev[u] = lev[p] + 1;
  par[u][0] = p;
  for (int i = 1; i < 20; i++) {
    par[u][i] = par[par[u][i-1]][i-1];
  }
  for (auto e: adj[u]) {
    int v = e.first, w = e.second;
    if (v == p) continue;
    dis[v] = dis[u] + w;
    init_tree(v, u);
  }
}

int get_ancestor(int u, int t_lev) {
  for (int i = 19; i >= 0; i--) {
    if (lev[u] - (1<<i) >= t_lev) {
      u = par[u][i];
    }
  }
  return u;
}

int get_lca(int a, int b) {
  if (lev[a] != lev[b]) {
    if (lev[a] < lev[b]) swap(a, b);
    a = get_ancestor(a, lev[b]);
  }
  if (a == b) return a;
  for (int i = 19; i >= 0; i--) {
    int na = par[a][i], nb = par[b][i];
    if (na != nb) a = na, b = nb;
  }
  return par[a][0];
}

int get_dist(int a, int b) {
  int lca = get_lca(a, b);
  return dis[a] + dis[b] - 2*dis[lca];
}

int main(void)
{
  ios::sync_with_stdio(0); cin.tie(0);
  int n; cin >> n;
  for (int i = 1; i < n; i++) {
    int a, b, w; cin >> a >> b >> w;
    adj[a].emplace_back(b, w);
    adj[b].emplace_back(a, w);
  }
  init_tree(1, 0);
  int m; cin >> m;
  for (int i = 0; i < m; i++) {
    int a, b; cin >> a >> b;
    cout << get_dist(a, b) << '\n';
  }
}
