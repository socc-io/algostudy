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
  void input() {
    cin >> x >> y;
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
    while (rs.size() >= 2 && ccw(rs[rs.size()-2], rs.back(), p) <= 0)
      rs.pop_back();
    rs.push_back(p);
  }
  return rs;
}

int n;
vector<point> ps;

int main(void)
{
  ios_base::sync_with_stdio(false); cin.tie(0);
  cin >> n;
  ps.resize(n);
  for (int i = 0; i < n; i++) ps[i].input();
  vector<point> hull = graham_scan(ps);
  printf("%lu\n", hull.size());
}
