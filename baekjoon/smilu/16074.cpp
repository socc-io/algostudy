#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
  int w, u, v;
  Edge() {}
  Edge(int w, int u, int v): w(w),u(u),v(v) {}
  bool operator<(const Edge &e) const { return w < e.w; }
};

struct Adj {
  int v, w;
  Adj(int v, int w): v(v),w(w) {}
};

int h, w, q;
int hei[500][500];
Edge edges[500000];
int edges_n;

int n;
int grp[250001];
int par[250001][20];
int sw[250001];
int mw[250001][20];
int lev[250001];
vector<Adj> adj[250001];

int getgrp(int u) { return grp[u] == u ? u : (grp[u] = getgrp(grp[u])); }
bool merge(int a, int b) {
  int ga = getgrp(a), gb = getgrp(b);
  if (ga == gb) return false;
  grp[ga] = gb;
  return true;
}

void prepare_edges() {
  const int dd[2][2] = {{1,0},{0,1}};
  for (int x = 0; x < h; x++) {
    for (int y = 0; y < w; y++) {
      int u = x*w+y;
      for (int di = 0; di < 2; di++) {
        int nx = x+dd[di][0], ny = y+dd[di][1];
        if (nx < 0 || nx >= h || ny < 0 || ny >= w) continue;
        int v = nx*w+ny;
        int w = max(hei[x][y], hei[nx][ny]);
        edges[edges_n++] = Edge(w, u+1, v+1);
        sw[u+1] = hei[x][y];
        sw[v+1] = hei[nx][ny];
      }
    }
  }
  sort(edges, edges+edges_n);
  for (int i = 0; i <= n; i++) grp[i] = i;
  for (int i = 0; i < edges_n; i++) {
    const Edge &e = edges[i];
    if (merge(e.u, e.v)) {
      adj[e.u].push_back(Adj(e.v, e.w));
      adj[e.v].push_back(Adj(e.u, e.w));
    }
  }
}

void build_tree(int u, int p, int w) {
  lev[u] = lev[p] + 1;
  par[u][0] = p;
  for (int i = 1; i < 20; i++) {
    par[u][i] = par[par[u][i-1]][i-1];
  }
  mw[u][0] = w;
  for (int i = 1; i < 20; i++) {
    mw[u][i] = max(mw[u][i-1], mw[par[u][i-1]][i-1]);
  }
  for (auto &e: adj[u]) {
    if (e.v == p) continue;
    build_tree(e.v, u, e.w);
  }
}

int find_ancestor(int a, int l) {
  for (int i = 19; i >= 0; i--) {
    if (lev[a] - (1<<i) < l) continue;
    a = par[a][i];
  }
  return a;
}

int find_lca(int a, int b) {
  if (lev[a] != lev[b]) {
    if (lev[a] < lev[b]) swap(a, b);
    a = find_ancestor(a, lev[b]);
  }
  if (a == b) return a;
  for (int i = 19; i >= 0; i--) {
    int aa = par[a][i], ab = par[b][i];
    if (aa == ab) continue;
    a = aa; b = ab;
  }
  return par[a][0];
}

int query_topdown(int a, int c) {
  int ret = 0;
  for (int i = 19; i >= 0; i--) {
    if (lev[c] - (1<<i) < lev[a]) continue;
    ret = max(ret, mw[c][i]);
    c = par[c][i];
  }
  return ret;
}

int query(int a, int b) {
  if (a == b) return sw[a];
  int lca = find_lca(a, b);
  return max(query_topdown(lca, a), query_topdown(lca, b));
}

int main(void)
{
  scanf("%d%d%d", &h, &w, &q);
  n = h*w;
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      scanf("%d", &hei[i][j]);
    }
  }
  prepare_edges();
  build_tree(1, 0, 0);
  for (int i = 0; i < q; i++) {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    int x = (x1-1) * w + (y1-1) + 1;
    int y = (x2-1) * w + (y2-1) + 1;
    printf("%d\n", query(x, y));
  }
}
