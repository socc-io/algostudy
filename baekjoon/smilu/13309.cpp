#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define SZ 200001

struct Seg {
  bool v[4*SZ];
  Seg() {
    for (int i = 0; i < 4*SZ; i++) v[i] = true;
  }
  void update(int n, int s, int e, int x) {
    if (x < s || x > e) return;
    if (s == e) { v[n] = false; return; }
    int l = n<<1, r = l|1, m = (s+e)>>1;
    update(l,s,m,x); update(r,m+1,e,x);
    v[n] = v[l] && v[r];
  }
  bool query(int n, int s, int e, int f, int t) {
    if (t < s || e < f) return true;
    if (f <= s && e <= t) return v[n];
    int l = n<<1, r = l|1, m = (s+e)>>1;
    return query(l, s, m, f, t) && query(r, m+1, e, f, t);
  }
} seg;

int n, q;
vector<int> chd[SZ];
int par[SZ];
int lev[SZ];
int wei[SZ];

int ct[SZ];
int nn[SZ], nnk = 1;

void build_tree(int u, int p) {
  lev[u] = lev[p] + 1;
  wei[u] = 1;
  for (int i = 0; i < chd[u].size(); i++) {
    int v = chd[u][i];
    build_tree(v, u);
    wei[u] += wei[v];
    if (wei[v] > wei[chd[u][0]]) swap(chd[u][0], chd[u][i]);
  }
}

void build_hld(int u, int pct) {
  nn[u] = nnk++;
  ct[u] = pct;
  for (int i = 0; i < chd[u].size(); i++) {
    int v = chd[u][i];
    build_hld(v, i == 0 ? pct : v);
  }
}

bool query(int a, int b) {
  while (ct[a] != ct[b]) {
    if (lev[ct[a]] < lev[ct[b]]) swap(a, b);
    if (!seg.query(1, 1, n, nn[ct[a]], nn[a])) return false;
    a = par[ct[a]];
  }
  if (lev[a] > lev[b]) swap(a, b);
  return seg.query(1, 1, n, nn[a]+1, nn[b]);
}

int main(void)
{
  scanf("%d%d", &n, &q);
  for (int i = 2; i <= n; i++) {
    scanf("%d", &par[i]);
    chd[par[i]].emplace_back(i);
  }
  build_tree(1, 0);
  build_hld(1, 1);

  for (int i = 0; i < q; i++) {
    int b, c, d; scanf("%d%d%d", &b, &c, &d);
    bool res = query(b, c);
    puts(res ? "YES" : "NO");
    if (d) {
      if (res) seg.update(1, 1, n, nn[b]);
      else seg.update(1, 1, n, nn[c]);
    }
  }
}
