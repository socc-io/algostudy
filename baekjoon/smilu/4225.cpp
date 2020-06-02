#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct point {
  ll x, y;
};

double tri_area(const point &a, const point &b, const point &c) {
  double ret = a.x*b.y
             - b.x*a.y
             + b.x*c.y
             - c.x*b.y
             + c.x*a.y
             - a.x*c.y;
  return ret / 2;
}

double dist(const point &a, const point &b) {
  double dx = a.x - b.x;
  double dy = a.y - b.y;
  return sqrt(dx*dx + dy*dy);
}

double dist_line_point(const point &a, const point &b, const point &c) {
  double area = (double)tri_area(a, b, c);
  return 2 * area / dist(a, b);
}

double solve(const vector<point> &ps) {
  int n = ps.size();
  double ret = DBL_MAX;
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      double min_v = 0, max_v = 0;
      for (int k = 0; k < n; k++) {
        min_v = min(min_v, dist_line_point(ps[i], ps[j], ps[k]));
        max_v = max(max_v, dist_line_point(ps[i], ps[j], ps[k]));
      }
      ret = min(ret, max_v - min_v);
    }
  }
  return ceil(ret*100)/100;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed;
  cout.precision(2);
  int piv = 0;
  while (1) {
    int n; cin >> n;
    if (n == 0) break;
    vector<point> ps(n);
    for (int i = 0; i < n; i++) cin >> ps[i].x >> ps[i].y;
    cout << "Case " << ++piv << ": " << solve(ps) << '\n';
  }
}
