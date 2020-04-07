#include <cstdio>
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
  bool operator<(const point &b) const {
    if (x == b.x) return y < b.y;
    return x < b.x;
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
vector<point> graham_scan(vector<point> &ps) {
  int n = ps.size();
  if (n <= 3) return ps;

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

bool is_inside(const vector<point> &ps, const point &p) {
  if(ps.size() == 2) {
    point ab = ps[0] - p;
    point ac = ps[1] - p;
    if (cross(ab, ac) == 0) {
      return ab.x * ac.x < 0;
    }
    return false;
  }

  int crosses = 0;
  for(int i = 0 ; i < ps.size() ; i++){
    int j = (i+1) % ps.size();
    if((ps[i].y > p.y) != (ps[j].y > p.y) ){
      double atX = (ps[j].x- ps[i].x)*(p.y-ps[i].y)/(ps[j].y-ps[i].y)+ps[i].x;
      if(p.x < atX)
        crosses++;
    }
  }
  return crosses % 2 > 0; 
}

bool is_line_cross(point p1, point p2, point q1, point q2) {
  point a = p1, b = p2 - p1, c = q1, d = q2 - q1;
  lld bt = cross(b, d);
  if (bt == 0) {
    if (cross(p1 - q1, p2 - q1) == 0) {
      if (p2 < p1) swap(p1, p2);
      if (p1 < q1 && q1 < p2) return true;
      return p1 < q2 && q2 < p2;
    } else return false;
  }
  lld tt = cross(c - a, d);
  return 0 <= tt && tt <= bt;
}

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<point> bp(n);
  vector<point> wp(m);
  for (int i = 0; i < n; i++) scanf("%lld%lld", &bp[i].x, &bp[i].y);
  for (int i = 0; i < m; i++) scanf("%lld%lld", &wp[i].x, &wp[i].y);
  if (n == 2 && m == 2) {
    bool ans = !is_line_cross(bp[0], bp[1], wp[0], wp[1]);
    puts(ans ? "YES" : "NO");
    return;
  }
  vector<point> bs = graham_scan(bp);
  vector<point> ws = graham_scan(wp);
  bool ans = true;
  for (const point &p: ws) {
    if (is_inside(bs, p)) {
      ans = false;
      break;
    }
  }
  if (ans) {
    for (const point &p: bs) {
      if (is_inside(ws, p)) {
        ans = false;
        break;
      }
    }
  }
  puts(ans ? "YES" : "NO");
}

int main(void)
{
  int t;
  scanf("%d", &t);
  while(t--) solve();
}
