#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define INF 0x7FFFFFFF
#define MAX_N 100010
#define V_SIZE (4*MAX_N)

typedef pair<int,int> pii;

struct MaxSegmentTree {
  int v[V_SIZE];
  MaxSegmentTree(int init = -INF) {
    for (int i = 0; i < V_SIZE; i++) v[i] = init;
  }
  void _update(int node, int begin, int end, int index, int value) {
    if (index < begin || index >= end) return;
    if (begin + 1 == end) {
      v[node] = value;
      return;
    }
    int mid = (begin + end) >> 1;
    _update(node<<1, begin, mid, index, value);
    _update((node<<1)+1, mid, end, index, value);
    v[node] = max(v[node<<1], v[(node<<1)+1]);
  }
  int _get(int node, int begin, int end, int from, int to) {
    if (end <= from || begin >= to) return -INF;
    if (from <= begin && end <= to) return v[node];
    int mid = (begin + end) >> 1;
    return max(
      _get(node<<1, begin, mid, from, to),
      _get((node<<1)+1, mid, end, from, to)
    );
  }
  int size = MAX_N;
  void update(int index, int value) {
    // printf("update %d = %d\n", index, value);
    _update(1, 0, size, index, value);
  }
  int get(int from, int to) {
    // printf("get %d, %d\n", from, to);
    return _get(1, 0, size, from, to); 
  }
};

struct edge {
  int v;
  int w;
  edge() {}
  edge(int v, int w): v(v), w(w) {}
};

MaxSegmentTree tree;

int n, m;
pii ed[MAX_N];
vector<edge> edges[MAX_N];

int chain[MAX_N]; int chain_index; // chain index
int indices[MAX_N]; int max_index; // segment tree index
int t_chain[MAX_N]; // top of chain
int c_child[MAX_N]; // chain child

int level[MAX_N];
int sz[MAX_N]; // node size
int pars[MAX_N][20]; // parents
int wp[MAX_N]; // weight to parent

int lca(int p, int q) {
  if (level[p] < level[q]) swap(p, q);
  for (int i = 19; i >= 0; i--) {
    int t = pars[p][i];
    if (level[t] < level[q]) continue;
    p = t;
  }
  if (p == q) return p;
  for (int i = 19; i >= 0; i--) {
    int pt = pars[p][i], qt = pars[q][i];
    if (pt == qt) continue;
    p = pt; q = qt;
  }
  return pars[p][0];
}

void make_tree(int u, int par) {
  sz[u] = 1;
  for (auto &e: edges[u]) {
    int v = e.v;
    if (v == par) continue;
    pars[v][0] = u;
    for (int i = 1; i < 20; i++) {
      int m = pars[v][i-1];
      pars[v][i] = pars[m][i-1];
    }
    wp[v] = e.w;
    level[v] = level[u] + 1;
    make_tree(v, u);
    sz[u] += sz[v];
    if (c_child[u] == 0 || sz[v] > sz[c_child[u]]) {
      c_child[u] = v;
    }
  }
}

void make_chain(int u, int par) {
  chain[u] = chain_index;
  indices[u] = max_index++;
  tree.update(indices[u], wp[u]);
  if (t_chain[chain_index] == 0) {
    t_chain[chain_index] = u;
  }
  if (c_child[u]) make_chain(c_child[u], u);
  for (auto &e: edges[u]) {
    int v = e.v;
    if (v == c_child[u] || v == par) continue;
    ++chain_index;
    make_chain(v, u);
  }
}

int max_w(int u, int v) {
  int res = 0;
  while (chain[u] != chain[v]) {
    int c = chain[v];
    int t = t_chain[c];
    res = max(res, tree.get(indices[t], indices[v]+1));
    v = pars[t][0];
  }
  res = max(res, tree.get(indices[u]+1, indices[v]+1));
  return res;
}

void update(int index, int value) {
  int u = ed[index].first, v = ed[index].second;
  if (level[u] > level[v]) swap(u, v);
  tree.update(indices[v], value);
}

int query(int p, int q) {
  int t = lca(p, q);
  return max(max_w(t, p), max_w(t, q));
}

int main(void)
{
  scanf("%d", &n);
  for (int i = 0; i < n-1; i++) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    edges[u].emplace_back(v, w);
    edges[v].emplace_back(u, w);
    ed[i+1] = {u, v};
  }
  chain_index = 1;
  max_index = 1;
  level[1] = 1;
  make_tree(1, 0);
  make_chain(1, 0);
  
  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    int cmd, a, b;
    scanf("%d%d%d", &cmd, &a, &b);
    if (cmd == 1) {
      update(a, b);
    } else {
      printf("%d\n", query(a, b));
    }
  }
}
