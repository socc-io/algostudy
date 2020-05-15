#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// const int L_INF  = 0x7f7f7f7f;
const ll  LL_INF = 0x7f7f7f7f7f7f7f7f;

const int MAX_N = 150001;

ll ans;
ll x[MAX_N];
ll y[MAX_N];

struct Point {
  ll x, y;
  bool operator<(const Point &p) const {
    if (x != p.x) return x < p.x;
    return y < p.y;
  }
  Point(ll x, ll y):x(x),y(y) {}
  Point() {}
};

struct Seg {
  Point ps[MAX_N*4];
  void build(int n, int s, int e) {
    if (s == e) {
      ps[n] = Point(y[s], s);
    } else {
      int m = (s+e)>>1, l = n<<1, r = l|1;
      build(l,s,m); build(r,m+1,e);
      ps[n] = min(ps[l], ps[r]);
    }
  }
  Point query(int n, int s, int e, int f, int t) {
    if (t < s || e < f) return Point(LL_INF, LL_INF);
    if (f <= s && e <= t) return ps[n];
    int m = (s+e)>>1, l = n<<1, r = l|1;
    return min(query(l,s,m,f,t),query(r,m+1,e,f,t));
  }
} seg;

int n, k;
priority_queue<ll> pq;

ll h;
ll get_area(int s, int e) {
  if (s >= e) return 0;
  int i = seg.query(1,1,n,s,e-1).y;
  ll prev_h = h;
  h = y[i];
  ll sub1 = get_area(s,i);
  ll sub2 = get_area(i+1, e);
  pq.push(min(sub1, sub2));
  h = prev_h;
  return max(sub1, sub2) + (x[e] - x[s]) * (y[i] - h);
}

int main(void)
{
  scanf("%d", &n); n >>= 1;
  for (int i = 1; i <= n; i++) {
    scanf("%lld%lld", x+i, y+i);
    scanf("%lld%lld", x+i, y+i);
  }
  seg.build(1,1,n);
  pq.push(get_area(1,n));
  scanf("%d", &k);
  for (int i = 0; i < k; i++) {
    if (pq.empty()) break;
    ans += pq.top(); pq.pop();
  }
  printf("%lld\n", ans);
}
