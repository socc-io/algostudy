#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

int ccw(pll a, pll b, pll c) {
  ll op  = a.first *b.second + b.first *c.second + c.first *a.second;
     op -= a.second*b.first  + b.second*c.first  + c.second*a.first ;
  if      (op >  0)    return  1;
  else if (op == 0)    return  0;
  else /* (op <  0) */ return -1;
}

bool inside(pll p, pll a, pll b) {
  if (ccw(a, b, p)) return false;
  if (a > b) swap(a, b);
  return a <= p && p <= b;
}

int is_intersect(pair<pll, pll> x, pair<pll, pll> y) {
  pll a = x.first;
  pll b = x.second;
  pll c = y.first;
  pll d = y.second;
  int c_abc = ccw(a, b, c);
  int c_abd = ccw(a, b, d);
  int c_cda = ccw(c, d, a);
  int c_cdb = ccw(c, d, b);
  int ab = c_abc * c_abd;
  int cd = c_cda * c_cdb;
  if (c_abc == 0 && c_abd == 0 && c_cda == 0 && c_cdb == 0) {
    if (c > d) swap(c, d);
    if (a < b) {
      if (d == a) return 1;
      return (c < b && a <= d) * 4;
    } else {
      if (c == a) return 1;
      return (c <= a && b < d) * 4;
    }
  }
  return ab <= 0 && cd <= 0 && !inside(b, c, d);
}

int solve() {
  ll mx, my, Mx, My;
  cin >> mx >> my >> Mx >> My;
  ll x1, y1, x2, y2;
  cin >> x1 >> y1 >> x2 >> y2;

  pair<pll, pll> line = {{x1, y1}, {x2, y2}};

  int r0 = is_intersect({{mx, my}, {Mx, my}}, line);
  int r1 = is_intersect({{Mx, my}, {Mx, My}}, line);
  int r2 = is_intersect({{Mx, My}, {mx, My}}, line);
  int r3 = is_intersect({{mx, My}, {mx, my}}, line);

  // cout << r0 << ' ';
  // cout << r1 << ' ';
  // cout << r2 << ' ';
  // cout << r3 << '\n';

  int r = r0 + r1 + r2 + r3;
  return min(r, 4);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  // cout << is_intersect({{0, 1}, {0, 0}}, {{0, 1}, {0, 2}});
  int t; cin >> t;
  while (t--) cout << solve() << '\n';
}
