#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<int> e[200];
bool visiting[200];
int h[200]; // height
int par[200];
int cyc[200];

bool inc_cyc(int u, int v) {
  bool res = true;
  while (u != v) {
    cyc[u]++;
    if (cyc[u] > 1) res = false;
    u = par[u];
  }
  return res;
}

int find_parent(int v1, int v2) {
  if (h[v1] > h[v2]) swap(v1, v2);
  while (h[v1] != h[v2]) v2 = par[v2];
  while (v1 != v2) {
    v1 = par[v1];
    v2 = par[v2];
  }
  return v1;
}

bool dfs(int u) {
  bool res = true;
  for (int v: e[u]) {
    if (v == par[u]) continue;
    if (h[v]) {
      if(h[v] < h[u]) continue;
      int w = find_parent(u, v);
      if (!inc_cyc(u, w)) res = false;
      if (!inc_cyc(v, w)) res = false;
      cyc[w]++;
      if (cyc[w] > 1) res = false;
      continue;
    }
    h[v] = h[u] + 1;
    par[v] = u;
    if (!dfs(v)) res = false;
  }
  return res;
}

int main(void)
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    int from, to;
    scanf("%d%d", &from, &to);
    --from; --to;
    e[from].push_back(to  );
    e[to  ].push_back(from);
  }

  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (h[i] != 0) continue;
    h[i] = 1;
    par[i] = -1;
    ans += dfs(i);
  }
  printf("%d\n", ans);
}
