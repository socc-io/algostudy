#include <bits/stdc++.h>
using namespace std;

void init_sz(
  const vector<vector<int>> &adj,
  vector<int> &sz,
  int u,
  int p
) {
  sz[u] = 1;
  for (int &v: adj[u]) if (v != p) {
    init_sz(adj, sz, v, u);
    sz[u] += sz[v];
    if (sz[v] > sz[adj[u][0]]) swap(v, adj[u][0]);
  }
}

void init_hld(
  const vector<vector<int>> &adj,
  const vector<int> &sz,
  vector<int> &in,
  vector<int> &top,
  int u,
  int p
) {
  int piv = in[u] + 1;
  for (int v: adj[u]) if (v != p) {
    in[v] = piv;
    piv += sz[v];
    top[v] = (v == adj[u][0] ? top[u] : v);
    init_hld(adj, sz, in, top, v, u);
  }
}
