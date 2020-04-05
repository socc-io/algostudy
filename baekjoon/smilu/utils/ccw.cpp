#include <vector>
using namespace std;

typedef long long lld;
typedef pair<lld, lld> pdd;

int ccw(pdd a, pdd b, pdd c) {
  lld op = a.first*b.second + b.first*c.second + c.first*a.second;
  op -= (a.second*b.first + b.second*c.first + c.second*a.first);
  if (op > 0) return 1;
  else if (op == 0) return 0;
  else return -1;
}

int is_intersect(pair<pdd, pdd> x, pair<pdd, pdd> y) {
  pdd a = x.first;
  pdd b = x.second;
  pdd c = y.first;
  pdd d = y.second;
  int ab = ccw(a, b, c)*ccw(a, b, d);
  int cd = ccw(c, d, a)*ccw(c, d, b);
  if (ab == 0 && cd == 0) {
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);
    return c <= b && a <= d;
  }
  return ab <= 0 && cd <= 0;
}
