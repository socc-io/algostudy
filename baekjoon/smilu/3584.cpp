#include <bits/stdc++.h>
using namespace std;

int par[10001][15];
int lev[10001];
bool chd[10001];
vector<int> adj[10001];

void init_tree(int u, int p) {
  lev[u] = lev[p] + 1;
  par[u][0] = p;
  for (int i = 1; i < 15; i++) {
    int m = par[u][i-1];
    par[u][i] = par[m][i-1];
  }
  for (int v: adj[u]) {
    if (v == p) continue;
    init_tree(v, u);
  }
}

int get_ancestor(int x, int t_lev) {
  for (int i = 14; i >= 0; i--) {
    if (lev[x] - (1<<i) >= t_lev) {
      x = par[x][i];
    }
  }
  return x;
}

int lca(int a, int b) {
  if (lev[a] != lev[b]) {
    if (lev[a] < lev[b]) swap(a, b);
    a = get_ancestor(a, lev[b]);
  }
  if (a == b) return a;
  for (int i = 14; i >= 0; i--) {
    int na = par[a][i], nb = par[b][i];
    if (na != nb) a = na, b = nb;
  }
  return par[a][0];
}

int solve() {
  int n; cin >> n;
  memset(chd, 0x00, sizeof(chd));
  for (int i = 0; i <= n; i++) adj[i].clear();
  for (int i = 1; i < n; i++) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    chd[b] = true;
  }
  int rt = -1;
  for (int i = 1; i <= n; i++) if (chd[i] == 0) rt = i;
  init_tree(rt, 0);
  int a, b; cin >> a >> b;
  return lca(a, b);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t;
  while (t--) {
    cout << solve() << '\n';
  }
}
