/*
Persistent Segment Tree
http://noj.am/11932
*/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_N 100010
#define MAX_M 100010

struct Seg {
  int v;
  Seg *l, *r;
  Seg(int v, Seg *l, Seg *r): v(v), l(l), r(r) {}
  Seg* build(int begin, int end, int nv) {
    if (nv >= begin && nv <= end) {
      if (begin == end) return new Seg(v+1, 0, 0);
      int mid = (begin + end) >> 1;
      return new Seg(v+1, l->build(begin, mid, nv), r->build(mid+1, end, nv));
    }
    return this;
  }
};

Seg *root[MAX_N];
int w[MAX_N], zp[MAX_N];
int par[MAX_N][20];
int lev[MAX_N];
vector<int> adj[MAX_N];
int n, m, sz;

void build_tree(int u, int p) {
  root[u] = root[p]->build(1, sz, w[u]);
  lev[u] = lev[p] + 1;
  par[u][0] = p;
  for (int v: adj[u]) {
    if (v == p) continue;
    build_tree(v, u);
  }
}

int find_ancestor(int a, int lv) {
  for (int i = 19; i >= 0; i--) {
    if (lev[a] - (1<<i) < lv) continue;
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
    if (par[a][i] == par[b][i]) continue;
    a = par[a][i];
    b = par[b][i];
  }
  return par[a][0];
}

int query(int begin, int end, Seg *a, Seg *b, Seg *lca, Seg *p_lca, int val) {
  if (begin == end) return begin;
  int len = a->l->v + b->l->v - lca->l->v - p_lca->l->v;
  int mid = (begin + end) >> 1;
  if (len >= val) return query(begin, mid, a->l, b->l, lca->l, p_lca->l, val);
  return query(mid+1, end, a->r, b->r, lca->r, p_lca->r, val - len);
}

int main(void)
{
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
  for (int i = 0; i < n; i++) zp[i] = w[i+1];
  int *zpe = unique(zp, zp+n);
  sz = zpe - zp;
  sort(zp, zpe);
  for (int i = 1; i <= n; i++) w[i] = lower_bound(zp, zpe, w[i]) - zp + 1;

  for (int i = 1; i < n; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    adj[x].emplace_back(y);
    adj[y].emplace_back(x);
  }

  root[0] = new Seg(0, 0, 0);
  root[0]->l = root[0]; root[0]->r = root[0];

  build_tree(1, 0);
  for (int i = 1; i < 20; i++) {
    for (int j = 1; j <= n; j++) {
      par[j][i] = par[par[j][i-1]][i-1];
    }
  }

  for (int i = 0; i < m; i++) {
    int x, y, k;
    scanf("%d%d%d", &x, &y, &k);
    int lca = find_lca(x, y);
    int p_lca = par[lca][0];
    int res = query(1, sz, root[x], root[y], root[lca], root[p_lca], k);
    printf("%d\n", zp[res-1]);
  }
}
