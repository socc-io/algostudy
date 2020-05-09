#include <cstdio>
#include <vector>
using namespace std;

#define MAX_N 100010

struct UnionFind {
  int par[MAX_N];
  int get(int x) { return x == par[x] ? x : (par[x] = get(par[x])); }
  int merge(int a, int b) {
    a = get(a); b = get(b);
    if (a == b) return 0;
    par[b] = a;
    return 1;
  }
  void clear() { for (int i = 0; i < MAX_N; i++) par[i] = i; }
  UnionFind() { clear(); }
} uf;

struct Edge {
  int u, v;
};
vector<Edge> bridges;

int n;
vector<int> adj[MAX_N];
int low[MAX_N];
int dfn[MAX_N];
int piv;

void build_tree(int u, int p) {
  dfn[u] = low[u] = ++piv;
  bool skip_par = false;
  for (int v: adj[u]) {
    if (v == u) continue;
    if (v == p && !skip_par) {
      skip_par = true;
      continue;
    }
    if (dfn[v] == 0) {
      build_tree(v, u);
      if (low[v] == dfn[v]) bridges.push_back({u, v});
      else {
        uf.merge(u, v);
      }
    }
    low[u] = min(low[u], low[v]);
  }
}

pair<int, int> dfs(int h, int p) {
    vector<pair<int, int> > v2;
    vector<int> v1;
    for (auto it : adj[h]) {
        if (it == p) continue;
        pair<int, int> p = dfs(it, h);
        if (!p.second) v1.push_back(p.first);
        else v2.push_back(p);
    }
    if (v1.size() + v2.size() == 0) return{ h,0 };
    for (int i = 1; i < v2.size(); i += 2) {
        printf("%d %d\n", v2[i - 1].first, v2[i].first);
        v1.push_back(v2[i - 1].second);
        v1.push_back(v2[i].second);
    }
    if (v1.empty()) return v2.back();
    if (v2.size() % 2) {
        printf("%d %d\n", v2.back().first, v1.back());
        v1.back() = v2.back().second;
    }
    for (int i = 1; i < v1.size() - 1; i += 2) printf("%d %d\n", v1[i - 1], v1[i]);
    if (v1.size() % 2) return{ v1.back(),0 };
    return{ v1[v1.size() - 2],v1.back() };
}

int main(void)
{
  int m; scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    int a, b; scanf("%d%d", &a, &b);
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  build_tree(1, 0);
  for (int i = 1; i <= n; i++) adj[i].clear();
  for (auto e: bridges) {
    int a = uf.get(e.u), b = uf.get(e.v);
    // printf("%d <=> %d\n", a, b);
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  int l_cnt = 0;
  for (int i = 1; i <= n; i++) l_cnt += adj[i].size() == 1;
  printf("%d\n", (l_cnt+1)>>1);

  pair<int,int> p = dfs(1, 0);
  if (adj[1].size() == 1) {
    if (p.first && p.second) printf("%d %d\n%d %d\n", 1, p.first, 1, p.second);
    else if (p.first) printf("%d %d\n", 1, p.first);
  } else if (adj[1].size() > 1) {
    if (p.first && p.second) printf("%d %d", p.first, p.second);
    else printf("%d %d", 1, p.first);
  }
}
