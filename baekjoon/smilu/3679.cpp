#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct point {
  ll x, y;
  int index;
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

vector<point> solve() {
  int n; cin >> n;
  vector<point> ps(n);
  for (int i = 0; i < n; i++) {
    cin >> ps[i].x >> ps[i].y;
    ps[i].index = i;
  }
  swap(ps[0], *min_element(ps.begin(), ps.end()));
  sort(ps.begin() + 1, ps.end(), [&](point a, point b) {
    ll dir = ccw(ps[0], a, b);
    if (dir) return dir > 0;
    return (ps[0]-a).abs2() < (ps[0]-b).abs2();
  });
  int piv = n-1;
  while (ccw(ps[0], ps[piv-1], ps[piv]) == 0) --piv;
  reverse(ps.begin() + piv, ps.end());
  return ps;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t;
  while (t--) {
    auto r = solve();
    for (point v: r) cout << v.index << ' ';
    cout << '\n';
  }
}
