#include <vector>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

int ccw(pll a, pll b, pll c) {
  ll op = a.first*b.second + b.first*c.second + c.first*a.second;
  op -= (a.second*b.first + b.second*c.first + c.second*a.first);
  if (op > 0) return 1;
  else if (op == 0) return 0;
  else return -1;
}

int is_intersect(pair<pll, pll> x, pair<pll, pll> y) {
  pll a = x.first;
  pll b = x.second;
  pll c = y.first;
  pll d = y.second;
  int ab = ccw(a, b, c)*ccw(a, b, d);
  int cd = ccw(c, d, a)*ccw(c, d, b);
  if (ab == 0 && cd == 0) {
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);
    return c <= b && a <= d;
  }
  return ab <= 0 && cd <= 0;
}

bool inside(pll p, pll a, pll b) {
  if (ccw(a, b, p)) return false;
  if (a > b) swap(a, b);
  return a <= p && p <= b;
}

int is_intersect_2(pair<pll, pll> x, pair<pll, pll> y) {
  // excluding point x.second
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
