#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

const int MAX_N = 100010;

int par[MAX_N][20];
ll wei[MAX_N][20];
int lev[MAX_N];
vector<pi> adj[MAX_N];

void init_tree(int u, int p) {
  lev[u] = lev[p] + 1;
  par[u][0] = p;
  for (int i = 1; i < 20; i++) {
    int m = par[u][i-1];
    par[u][i] = par[m][i-1];
    wei[u][i] = wei[u][i-1] + wei[m][i-1];
  }
  for (pi e: adj[u]) {
    int v = e.first, wa = e.second;
    if (v == p) continue;
    wei[v][0] = wa;
    init_tree(v, u);
  }
}

int ancestor(int x, int t_lev) {
  for (int i = 19; i >= 0; i--) {
    if (lev[x] - (1<<i) >= t_lev) x = par[x][i];
  }
  return x;
}

int lca(int a, int b) {
  if (lev[a] != lev[b]) {
    if (lev[a] < lev[b]) swap(a, b);
    a = ancestor(a, lev[b]);
  }
  if (a == b) return a;
  for (int i = 19; i >= 0; i--) {
    int na = par[a][i], nb = par[b][i];
    if (na != nb) a = na, b = nb;
  }
  return par[a][0];
}

ll weight(int x, int t_lev) {
  ll ret = 0;
  for (int i = 19; i >= 0; i--) {
    if (lev[x] - (1<<i) >= t_lev) {
      ret += wei[x][i];
      x = par[x][i];
    }
  }
  return ret;
}

ll query_1(int f, int t) {
  int m_lev = lev[lca(f, t)];
  return weight(f, m_lev) + weight(t, m_lev);
}

int query_2(int f, int t, int x) {
  const int m_lev = lev[lca(f, t)];
  if (lev[f] - m_lev < x) {
    return ancestor(t, (m_lev<<1) + x - lev[f]);
  } else {
    return ancestor(f, lev[f] - x);
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n; cin >> n;
  for (int i = 1; i < n; i++) {
    int a, b, w; cin >> a >> b >> w;
    adj[a].push_back({b, w});
    adj[b].push_back({a, w});
  }
  init_tree(1, 0);
  int q; cin >> q;
  while (q--) {
    int cm; cin >> cm;
    if (cm == 1) {
      int u, v; cin >> u >> v;
      cout << query_1(u, v) << '\n';
    } else if (cm == 2) {
      int u, v, k; cin >> u >> v >> k;
      cout << query_2(u, v, k-1) << '\n';
    }
  }
}
