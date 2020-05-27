#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pi;
typedef pair<int,pi> pii;

const int MAX_N = 100001;
const int MAX_H = 18;
const int L_INF = 0x7fffffff;

int n;
vector<pi> adj[MAX_N];
int par[MAX_N][MAX_H];
int min_vs[MAX_N][MAX_H];
int max_vs[MAX_N][MAX_H];
int lev[MAX_N];

void init_tree(int u, int p) {
  par[u][0] = p;
  for (int i = 1; i < MAX_H; i++) {
    int m = par[u][i-1];
    par[u][i] = par[m][i-1];
    min_vs[u][i] = min(min_vs[u][i-1], min_vs[m][i-1]);
    max_vs[u][i] = max(max_vs[u][i-1], max_vs[m][i-1]);
  }
  lev[u] = lev[p] + 1;
  for (pi e: adj[u]) {
    int v = e.first, w = e.second;
    if (v == p) continue;
    min_vs[v][0] = w;
    max_vs[v][0] = w;
    init_tree(v, u);
  }
}

pii get_ancestor(int u, int t_lev) {
  int mw = L_INF;
  int Mw = 0;
  for (int i = MAX_H-1; i >= 0; i--) {
    if (lev[u] - (1<<i) >= t_lev) {
      mw = min(mw, min_vs[u][i]);
      Mw = max(Mw, max_vs[u][i]);
      u = par[u][i];
    }
  }
  return {u, {mw, Mw}};
}

pii get_lca(int a, int b) {
  int mw = L_INF;
  int Mw = 0;
  if (lev[a] != lev[b]) {
    if (lev[a] < lev[b]) swap(a, b);
    pii tmp = get_ancestor(a, lev[b]);
    a = tmp.first;
    mw = min(mw, tmp.second.first);
    Mw = max(Mw, tmp.second.second);
  }
  if (a == b) return {a, {mw, Mw}};
  for (int i = MAX_H-1; i >= 0; i--) {
    int na = par[a][i], nb = par[b][i];
    if (na != nb) {
      mw = min(mw, min_vs[a][i]);
      mw = min(mw, min_vs[b][i]);
      Mw = max(Mw, max_vs[a][i]);
      Mw = max(Mw, max_vs[b][i]);
      a = na, b = nb;
    }
  }
  mw = min(mw, min_vs[a][0]);
  mw = min(mw, min_vs[b][0]);
  Mw = max(Mw, max_vs[a][0]);
  Mw = max(Mw, max_vs[b][0]);
  return {par[a][0], {mw, Mw}};
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  for (int i = 0; i < MAX_H; i++) {
    min_vs[0][i] = L_INF;
    min_vs[1][i] = L_INF;
  }
  cin >> n;
  for (int i = 1; i < n; i++) {
    int a, b, w; cin >> a >> b >> w;
    adj[a].emplace_back(b, w);
    adj[b].emplace_back(a, w);
  }
  init_tree(1, 0);
  int m; cin >> m;
  for (int i = 0; i < m; i++) {
    int a, b; cin >> a >> b;
    pii tmp = get_lca(a, b);
    cout << tmp.second.first << ' ' << tmp.second.second << '\n';
  }
}


