#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 100010;
const int MAX_H = 18;

int n;
vector<int> adj[MAX_N];
int par[MAX_N][MAX_H];
int lev[MAX_N];

void init_tree(int u, int p) {
  par[u][0] = p;
  for (int i = 1; i < MAX_H; i++) {
    par[u][i] = par[par[u][i-1]][i-1];
  }
  lev[u] = lev[p] + 1;
  for (int v: adj[u]) {
    if (v == p) continue;
    init_tree(v, u);
  }
}

int get_ancestor(int u, int t_lev) {
  for (int i = MAX_H-1; i >= 0; i--) {
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
  for (int i = MAX_H-1; i >= 0; i--) {
    int na = par[a][i], nb = par[b][i];
    if (na != nb) a = na, b = nb;
  }
  return par[a][0];
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n;
  for (int i = 1; i < n; i++) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  init_tree(1, 0);
  int m; cin >> m;
  for (int i = 0; i < m; i++) {
    int a, b; cin >> a >> b;
    cout << get_lca(a, b) << '\n';
  }
}
