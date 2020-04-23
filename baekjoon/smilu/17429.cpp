#include <cstdio>
#include <vector>
using namespace std;

typedef unsigned long long llu;

const int MAX_N = 500001;
const int MAX_V = 4*MAX_N;
const llu mod = 1LL<<32;

struct Seg {
  llu v[MAX_V];
  llu la[MAX_V];
  llu lb[MAX_V];
  Seg() {
    for (int i = 0; i < MAX_V; i++) {
      la[i] = 1;
    }
  }
  void lazy(int n, int s, int e) {
    if (la[n] == 1 && lb[n] == 0) return;
    int l = n<<1, r = l+1;
    if (e-s >= 2) {
      la[l] *= la[n]; la[l] %= mod;
      lb[l] *= la[n]; lb[l] %= mod;
      lb[l] += lb[n]; lb[l] %= mod;
      la[r] *= la[n]; la[r] %= mod;
      lb[r] *= la[n]; lb[r] %= mod;
      lb[r] += lb[n]; lb[r] %= mod;
    }
    v[n] *= la[n]; v[n] %= mod;
    v[n] += (e-s)*lb[n]; v[n] %= mod;
    la[n] = 1; lb[n] = 0;
  }
  void update(int n, int s, int e, int f, int t, llu mul, llu alp) {
    lazy(n, s, e);
    if (t <= s || e <= f) return;
    if (f <= s && e <= t) {
      la[n] *= mul; la[n] %= mod;
      lb[n] *= mul; lb[n] %= mod;
      lb[n] += alp; lb[n] %= mod;
      lazy(n, s, e);
      return;
    }
    int m = (s+e)>>1, l = n<<1, r = l+1;
    update(l, s, m, f, t, mul, alp);
    update(r, m, e, f, t, mul, alp);
    v[n] = v[l] + v[r]; v[n] %= mod;
    // printf("update(%d,%d,%d,%d,%d,%llu,%llu)\n", n, s, e, f, t, mul, alp);
  }
  llu query(int n, int s, int e, int f, int t) {
    lazy(n, s, e);
    if (t <= s || e <= f) return 0;
    if (f <= s && e <= t) return v[n];
    int m = (s+e)>>1, l = n<<1, r = l+1;
    llu ret = query(l, s, m, f, t) + query(r, m, e, f, t);
    ret %= mod;
    // printf("query(%d,%d,%d,%d,%d): %llu\n", n, s, e, f, t, ret);
    return ret;
  }
} seg;

int n, q;
vector<int> adj[MAX_N];
int lev[MAX_N];
int par[MAX_N];
int wei[MAX_N];
int hc[MAX_N];
int ct[MAX_N];
int ce[MAX_N];
int ix[MAX_N], ixn;
int ox[MAX_N];

void build_tree(int u, int p) {
  par[u] = p;
  lev[u] = lev[p] + 1;
  wei[u] = 1;
  for (int v: adj[u]) {
    if (v == p) continue;
    build_tree(v, u);
    wei[u] += wei[v];
    if (hc[u] == 0 || wei[v] > wei[hc[u]]) {
      hc[u] = v;
    }
  }
}

void build_hld(int u, int p, int t) {
  ix[u] = ixn++;
  ct[u] = t;
  if (hc[u]) build_hld(hc[u], u, t);
  else ce[t] = u;
  for (int v: adj[u]) {
    if (v == p || v == hc[u]) continue;
    build_hld(v, u, v);
  }
  ox[u] = ixn;
}

llu query_ab(int a, int b) {
  llu ans = 0;
  while (ct[a] != ct[b]) {
    if (lev[ct[a]] < lev[ct[b]]) swap(a, b);
    ans += seg.query(1, 0, n, ix[ct[a]], ix[a]+1);
    ans %= mod;
    a = par[ct[a]];
  }
  if (lev[a] > lev[b]) swap(a, b);
  ans += seg.query(1, 0, n, ix[a], ix[b]+1);
  return ans % mod;
}

void update_ab(int a, int b, llu mul, llu alp) {
  // printf("update_ab(%d,%d,%llu,%llu)\n", a, b, mul, alp);
  while (ct[a] != ct[b]) {
    if (lev[ct[a]] < lev[ct[b]]) swap(a, b);
    seg.update(1, 0, n, ix[ct[a]], ix[a]+1, mul, alp);
    a = par[ct[a]];
  }
  if (lev[a] > lev[b]) swap(a, b);
  seg.update(1, 0, n, ix[a], ix[b]+1, mul, alp);
}

llu query_st(int rt) {
  return seg.query(1, 0, n, ix[rt], ox[rt]);
}

void update_st(int rt, llu mul, llu alp) {
  return seg.update(1, 0, n, ix[rt], ox[rt], mul, alp);
}

int main(void)
{
  scanf("%d%d", &n, &q);
  for (int i = 1; i < n; i++) {
    int s, e; scanf("%d%d", &s, &e);
    adj[s].push_back(e);
    adj[e].push_back(s);
  }
  build_tree(1, 0);
  build_hld(1, 0, 1);
  for (int i = 0; i < q; i++) {
    int c, x, y, v;
    scanf("%d", &c);
    if (c == 1) {
      scanf("%d%d", &x, &v);
      update_st(x, 1, v);
    } else if (c == 2) {
      scanf("%d%d%d", &x, &y, &v);
      update_ab(x, y, 1, v);
    } else if (c == 3) {
      scanf("%d%d", &x, &v);
      update_st(x, v, 0);
    } else if (c == 4) {
      scanf("%d%d%d", &x, &y, &v);
      update_ab(x, y, v, 0);
    } else if (c == 5) {
      scanf("%d", &x);
      printf("%llu\n", query_st(x));
    } else if (c == 6) {
      scanf("%d%d", &x, &y);
      printf("%llu\n", query_ab(x, y));
    }
  }
}
