#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

struct Edge {
  int v, w;
};

int n, m, l;
vector<Edge> adj[100000];
int par[100000];
int par_w[100000];
int cp[100000];

pair<int,int> far(int u, int p, int pw) {
  par[u] = p;
  par_w[u] = pw;
  pair<int,int> ret = {u, 0};
  for (const auto &e: adj[u]) {
    int v = e.v, w = e.w;
    if (v == p) continue;
    auto res = far(v, u, w);
    int nw = w + res.second;
    if (nw > ret.second) {
      ret.first = res.first;
      ret.second = nw;
    }
  }
  return ret;
}

pair<int,pair<int,int>> center(int u) {
  u = far(u, u, 0).first;
  auto fr = far(u, u, 0);
  int v = fr.first, uv = fr.second, dm = uv;
  int ret = v, ret_sz = uv;
  while (v != u) {
    int sz = max(uv, dm - uv);
    if (sz < ret_sz) {
      ret = v;
      ret_sz = sz;
    }
    uv -= par_w[v];
    v = par[v];
  }
  return {ret, {ret_sz, dm}};
}

int main(void)
{
  scanf("%d%d%d", &n, &m, &l);
  for (int i = 0; i < m; i++) {
    int a, b, t;
    scanf("%d%d%d", &a, &b, &t);
    adj[a].push_back({b, t});
    adj[b].push_back({a, t});
  }
  int ans = 0;
  vector<int> rs;
  for (int i = 0; i < n; i++) par[i] = -1;
  for (int i = 0; i < n; i++) {
    if (par[i] != -1) continue;
    auto res = center(i);
    ans = max(ans, res.second.second);
    rs.push_back(res.second.first);
  }
  sort(rs.begin(), rs.end(), greater<int>());
  if (rs.size() > 1) {
    ans = max(ans, rs[0]+rs[1]+l);
    if (rs.size() > 2) {
      ans = max(ans, rs[1]+rs[2]+2*l);
    }
  }
  printf("%d\n", ans);
}
