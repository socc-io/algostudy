#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef long double lf;
typedef pair<int,int> pi;

struct UnionFind {
  int p[205];
  UnionFind() {
    for (int i = 0; i < 201; i++) p[i] = i;
  }
  int get(int x) { return x == p[x] ? x : (p[x] = get(p[x])); }
  bool merge(int a, int b) {
    a = get(a); b = get(b);
    if (a == b) return false;
    p[b] = a;
    return true;
  }
};

struct edge {
  int u, v, t, c;
  void input() { scanf("%d%d%d%d", &u, &v, &t, &c); }
} es[10005];

int n, m;
int p, q;
int rp = 1e9, rq = 1e9, rst = 1e9, rsc = 1e9;

pi test(int tp, int tq, bool verb) {
  UnionFind uf;
  int st = 0, sc = 0;
  p = tp; q = tq;
  sort(es, es+m, [&](const edge &a, const edge &b) {
    ll aw = 1ll * p * a.t + 1ll * q * a.c;
    ll bw = 1ll * p * b.t + 1ll * q * b.c;
    return aw < bw;
  });
  for (int i = 0; i < m; i++) {
    if (uf.merge(es[i].u, es[i].v)) {
      st += es[i].t; sc += es[i].c;
      if (verb) printf("%d %d\n", es[i].u, es[i].v);
    }
  }
  if (1ll*rst*rsc > 1ll*st*sc) {
    rst = st;
    rsc = sc;
    rp = tp;
    rq = tq;
  }
  return {st, sc};
}

bool ccw(pi a, pi b, pi c) {
  int p0 = b.first - a.first;
  int p1 = c.second - a.second;
  int p2 = b.second - a.second;
  int p3 = c.first - a.first;
  return 1ll*p0*p1 >= 1ll*p2*p3;
}

void dfs(pi s, pi e) {
  pi m = test(s.second - e.second, e.first - s.first, false);
  if (!ccw(e, m, s)) {
    dfs(s, m);
    dfs(m, e);
  }
}

int main(void)
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) es[i].input();
  pi up = test(1, 0, false);
  pi lo = test(0, 1, false);
  dfs(up, lo);
  printf("%d %d\n", rst, rsc);
  test(rp, rq, true);
}
