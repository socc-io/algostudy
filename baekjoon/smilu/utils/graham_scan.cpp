#include <vector>
#include <stack>
#include <algorithm>
#include <cmath>
using namespace std;

typedef long long lld;

struct point {
  lld x, y;
  point() {}
  point(lld _x, lld _y) { x = _x; y = _y; }
  point operator-(const point &b) const {
    return point(x - b.x, y - b.y);
  }
};
lld cross(point a, point b) {
  return a.x*b.y - a.y*b.x;
}
lld dot(point a, point b) {
  return a.x*b.x + a.y*b.y;
}
point gs_piv;
bool gs_cmp(point a, point b) {
  return cross(a-gs_piv, b-gs_piv) > 0;
}
vector<point> graham_scan(vector<point> ps) {
  int n = ps.size();

  int min_y = ps[0].y;
  int min_yi = 0;
  for (int i = 1; i < n; i++) {
    if (ps[i].y < min_y) {
      min_y = ps[i].y;
      min_yi = i;
    }
  }
  swap(ps[0], ps[min_yi]);
  gs_piv = ps[0];
  auto beg = ps.begin(); ++beg;
  sort(beg, ps.end(), gs_cmp);
  vector<point> s;
  s.push_back(gs_piv);
  s.push_back(ps[1]);
  for (int i = 2; i < n; i++) {
    bool parallel=false;
    while(s.size() >= 2) {
      auto top = s[s.size()-1];
      auto sec = s[s.size()-2];
      lld c = cross(top-sec, ps[i]-top);
      lld d = dot(top-sec, ps[i]-top);
      if(c > 0) break;
      else if (c == 0 && d < 0) {
        parallel=true;
        break;
      }
      s.pop_back();
    }
    if(!parallel) s.push_back(ps[i]);
  }

  return s;
}