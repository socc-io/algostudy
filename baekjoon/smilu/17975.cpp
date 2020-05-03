#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

inline ll max3(ll a, ll b, ll c) { return max(max(a, b), c); }

struct Seg {
  struct Node {
    ll sm, ls, rs, ms;
    Node(int v = 0) { clear(v); }
    Node(const Node &l, const Node &r) { join(l, r); }
    void clear(int v = 0) { sm = v; ls = v; rs = v; ms = v; }
    void join(const Node &l, const Node &r) {
      sm = l.sm + r.sm;
      ls = max3(l.ls, l.sm, l.sm+r.ls);
      rs = max3(r.rs, r.sm, r.sm+l.rs);
      ms = max3(l.ms, r.ms, l.rs+r.ls);
    }
    void update(ll val) { sm+=val; ls+=val; rs+=val; ms+=val; }
    ll get() { return max(max(sm,ls),max(rs,ms)); }
  };
  Node nd[8000];
  void clear() { for (int i = 0; i < 8000; i++) nd[i].clear(); }
  void update(int n, int s, int e, int x, int val) {
    if (x < s || x > e) return;
    if (s == e) { nd[n].update(val); return; }
    int m = (s+e)>>1, l = n<<1, r = l|1;
    update(l,s,m,x,val); update(r,m+1,e,x,val);
    nd[n].join(nd[l], nd[r]);
  }
  void update(int x, int val) { update(1,0,2000,x,val); }
  Node query(int n, int s, int e, int f, int t) {
    if (t < s || e < f) return Node();
    if (f <= s && e <= t) return nd[n];
    int m = (s+e)>>1, l = n<<1, r = l|1;
    return Node(query(l,s,m,f,t), query(r,m+1,e,f,t));
  }
  ll query(int f=0, int t=2000) { return query(1,0,2000,f,t).get(); }
} seg;

struct point {
  ll x, y, w;
  point() {}
  point(ll x, ll y, ll w): x(x),y(y),w(w) {}
  bool operator<(const point &p) const {
    if (x == p.x) return y < p.y;
    return x < p.x;
  }
} ps[2002];
int sn, bn, n;
ll c1, c2;
ll xs[2002], ys[2002];

int main(void)
{
  scanf("%d", &sn);
  for (int i = 0; i < sn; i++) scanf("%lld%lld", &ps[i].x, &ps[i].y);
  scanf("%d", &bn);
  for (int i = 0; i < bn; i++) scanf("%lld%lld", &ps[sn+i].x, &ps[sn+i].y);
  n = sn + bn;

  // Assign weights to the points
  scanf("%lld%lld", &c1, &c2);
  for (int i = 0; i < sn; i++) ps[i].w = c1;
  for (int i = 0; i < bn; i++) ps[sn+i].w = -c2;

  for (int i = 0; i < n; i++) ys[i] = ps[i].y;
  sort(ys,ys+n);
  auto yu = unique(ys, ys+n);
  for (int i = 0; i < n; i++) {
    ps[i].y = lower_bound(ys, yu, ps[i].y) - ys;
  }
  
  sort(ps, ps+n);
  
  ll ans = 0;
  for (int k = 0; k < n; k++) { // starting x
    while (ps[k].x == ps[k+1].x && k+1 < n) k++;
    seg.clear();
    int s = lower_bound(ps, ps+n, point(ps[k].x,0,0)) - ps;
    for (int i = s; i < n;) {
      int bx = ps[i].x; // x-value of batch (line x = bx)
      for (; ps[i].x == bx && i < n; i++) {
        seg.update(ps[i].y, ps[i].w);
      }
      ans = max(ans, seg.query());
    }
  }
  printf("%lld\n", ans);
}
