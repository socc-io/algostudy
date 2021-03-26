/*
https://www.acmicpc.net/problem/3878
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long lld;

struct point {
  lld x, y;
  point() {}
  point(lld x, lld y): x(x), y(y) {}
  bool operator<(const point &p) const {
    if (x == p.x) return y < p.y;
    return x < p.x;
  }
  point operator-(const point &p) const {
    return point(x - p.x, y - p.y);
  }
  lld abs2() {
    return x*x + y*y;
  }
};

lld ccw(point a, point b, point c) {
  return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}

vector<point> graham_scan(vector<point> &ps) { // convex hull
  vector<point> rs;
  swap(ps[0], *min_element(ps.begin(), ps.end()));
  sort(ps.begin() + 1, ps.end(), [&](point a, point b) {
    lld dir = ccw(ps[0], a, b);
    if (dir) return dir > 0;
    return (ps[0]-a).abs2() < (ps[1]-b).abs2();
  });
  for (auto p: ps) {
    while (rs.size() >= 2 && (ccw(rs[rs.size()-2], rs.back(), p) <= 0 || ccw(rs.back(), p, rs[0]) <= 0))
      rs.pop_back();
    rs.push_back(p);
  }
  return rs;
}

double tri_area(const point &a, const point &b, const point &c) {
  double ret = a.x*b.y
             - b.x*a.y
             + b.x*c.y
             - c.x*b.y
             + c.x*a.y
             - a.x*c.y;
  return ret / 2;
}

bool is_inside_poly(point p, const vector<point> &phs) {
  // @Args p: target point, phs: polygon hull points
  int cnt = 0; // collision count
  for (int i = 0; i < phs.size(); i++) {
    int j = (i + 1) % phs.size();
    point r1 = phs[i], r2 = phs[j];
    if ((p.y < r1.y) == (p.y < r2.y)) continue;
    double x = (double)(r2.x - r1.x) * (p.y - r1.y) / (r2.y - r1.y) + r1.x;
    if (p.x < x) ++cnt;
  }
  return cnt & 1;
}

bool disjoint(lld a, lld b, lld c, lld d) {
  if (a > b) swap(a, b);
  if (c > d) swap(c, d);
  return b < c || d < a;
}

bool is_crossing(point a, point b, point c, point d) {
  lld f1 = ccw(a, b, c) * ccw(a, b, d);
  lld f2 = ccw(c, d, a) * ccw(c, d, b);
  if (f1 == 0 && f2 == 0) {
    return !disjoint(a.x, b.x, c.x, d.x) && !disjoint(a.y, b.y, c.y, d.y);
  }
  return f1 <= 0 && f2 <= 0;
}

bool solve() {
  int n, m; cin >> n >> m;
  vector<point> aps(n), bps(m);
  for (int i = 0; i < n; i++) cin >> aps[i].x >> aps[i].y;
  for (int i = 0; i < m; i++) cin >> bps[i].x >> bps[i].y;
  vector<point> ahs = graham_scan(aps);
  vector<point> bhs = graham_scan(bps);

  for (point ap: ahs) if (is_inside_poly(ap, bhs)) return false;
  for (point bp: bhs) if (is_inside_poly(bp, ahs)) return false;
  
  for (int i = 0; i < ahs.size(); i++) {
    for (int j = 0; j < bhs.size(); j++) {
      if (is_crossing(
        ahs[i], ahs[(i + 1) % ahs.size()],
        bhs[j], bhs[(j + 1) % bhs.size()]
      )) return false;
    }
  }

  return true;
}

int main(void)
{
  ios_base::sync_with_stdio(false); cin.tie(0);
  int t; cin >> t;
  while(t--) puts(solve() ? "YES" : "NO");
}
