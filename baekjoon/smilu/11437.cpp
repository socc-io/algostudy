#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 50001;
const int MAX_H = 20;

int n;
int par[MAX_N][MAX_H];
int lev[MAX_N];
vector<int> adj[MAX_N];

void build_tree(int u, int p) {
  par[u][0] = p;
  lev[u] = lev[p] + 1;
  for (int i = 1; i < MAX_H; i++) {
    par[u][i] = par[par[u][i-1]][i-1];
  }
  for (int v: adj[u]) {
    if (v == p) continue;
    build_tree(v, u);
  }
}

int get_ancestor(int u, int target) {
  for (int i = MAX_H-1; i >= 0; i--) {
    if (lev[u] - (1<<i) >= target) u = par[u][i];
  }
  return u;
}

int find_lca(int a, int b) {
  if (lev[a] != lev[b]) {
    if (lev[a] < lev[b]) swap(a, b);
    a = get_ancestor(a, lev[b]);
  }
  if (a == b) return a;
  for (int i = MAX_H-1; i >= 0; i--) {
    int na = par[a][i], nb = par[b][i];
    if (na == nb) continue;
    a = na, b = nb;
  }
  return par[a][0];
}

int main(void)
{
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    int a, b; scanf("%d%d", &a, &b);
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  build_tree(1, 0);
  int m; scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    int a, b; scanf("%d%d", &a, &b);
    printf("%d\n", find_lca(a, b));
  }
}
