#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct pnt {
  ll x, y;
  ll hypot() const {
    return x*x+y*y;
  }
  ll ccw(const pnt &b) const {
    return x*b.y-y*b.x;
  }
  bool operator<(const pnt &b) const {
    if (x != b.x) return x < b.x;
    return y < b.y;
  }
  bool compare_angle(const pnt &b) const {
    if ((pnt(0, 0) < (*this)) ^ (pnt(0, 0) < b)) return b < (*this);
    ll t = ccw(b);
    if (t != 0) return t > 0;
    return hypot() < b.hypot();
  }
  pnt(ll x=0, ll y=0): x(x),y(y) {}
};
