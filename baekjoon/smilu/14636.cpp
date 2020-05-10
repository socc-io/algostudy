#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct point {
  ll x, y;
  point(ll x=0, ll y=0): x(x),y(y) {}
  ll area(const point &p) const {
    if (p.x <= x && p.y <= y) return 0;
    return (p.x-x)*(p.y-y);
  }
} L[500050], R[500050];
int n, m;

ll dnq(int s, int e, int l, int r) {
  if (s > e) return 0;
  int m = (s+e)>>1;
  int mx = l;
  ll mxval = L[m].area(R[l]);
  for (int p = l+1; p <= r; p++) {
    ll a = L[m].area(R[p]);
    if (a > mxval) {
      mxval = a;
      mx = p;
    }
  }
  ll l_ret = dnq(s,m-1,mx,r);
  ll r_ret = dnq(m+1,e,l,mx);
  return max(mxval, max(l_ret, r_ret));
}

int main(void)
{
  scanf("%d%d", &n, &m);

  for (int i = 0; i < n; i++) scanf("%lld%lld", &L[i].x, &L[i].y);
  for (int i = 0; i < m; i++) scanf("%lld%lld", &R[i].x, &R[i].y);

  int _n = 0, _m = 0;
  sort(L, L+n, [](const point &a, const point &b) {
    if (a.x != b.x)
      return a.x < b.x;
    return a.y < a.y;
  });
  _n = n > 0;
  for (int i = 1; i < n; i++) {
    if (L[i].y < L[_n-1].y)
      L[_n++] = L[i];
  }
  n = _n;
  
  sort(R, R+m, [](const point &a, const point &b) {
    if (a.x != b.x)
      return a.x > b.x;
    return a.y > a.y;
  });
  _m = m > 0;
  for (int i = 1; i < m; i++) {
    if (R[i].y > R[_m-1].y)
      R[_m++] = R[i];
  }
  m = _m;

  ll ans = dnq(0, n-1, 0, m-1);

  printf("%lld\n", ans);
}
