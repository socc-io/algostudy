#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct point {
  ll x, y;
  point() {}
  point(ll x, ll y): x(x), y(y) {}
  bool operator<(const point &p) const {
    if (x == p.x) return y < p.y;
    return x < p.x;
  }
  point operator-(const point &p) const {
    return point(x - p.x, y - p.y);
  }
  ll abs2() {
    return x*x + y*y;
  }
};

ll ccw(point a, point b, point c) {
  return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}

vector<point> graham_scan(vector<point> &ps) { // convex hull
  vector<point> rs;
  swap(ps[0], *min_element(ps.begin(), ps.end()));
  sort(ps.begin() + 1, ps.end(), [&](point a, point b) {
    ll dir = ccw(ps[0], a, b);
    if (dir) return dir > 0;
    return (ps[0]-a).abs2() < (ps[0]-b).abs2();
  });
  for (auto p: ps) {
    while (rs.size() >= 2 && ccw(rs[rs.size()-2], rs.back(), p) <= 0)
      rs.pop_back();
    rs.push_back(p);
  }
  return rs;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n; cin >> n;
  ll l; cin >> l;
  vector<point> ps(n);
  for (point &p: ps) cin >> p.x >> p.y;
  vector<point> hs = graham_scan(ps);
  n = hs.size();
  double ret = 0.0;
  for (int i = 0; i < n; i++) {
    const point &a = hs[i];
    const point &b = hs[(i+1)%n];
    ret += sqrt((a-b).abs2());
  }
  ret += 2.0*M_PI*l;
  cout << fixed << setprecision(0) << ret << '\n';
}
