#include <cstdio>
#include <vector>
using namespace std;

#define INF 0x7FFFFFFFFFFFFFF0

typedef long long lld;
typedef pair<lld, lld> pdd;

struct Position {
  lld x, y;
  bool operator<(const Position &p) const {
    if (x == p.x) return y < p.y;
    return x < p.x;
  }
  bool operator<=(const Position &p) const {
    if (x == p.x) return y <= p.y;
    return x <= p.x;
  }
  bool operator==(const Position &p) const {
    return x == p.x && y == p.y;
  }
};

int ccw(Position a, Position b, Position c) {
  lld op = a.x*b.y + b.x*c.y + c.x*a.y;
  op -= (a.y*b.x + b.y*c.x + c.y*a.x);
  if (op > 0) return 1;
  else if (op == 0) return 0;
  else return -1;
}

struct Line {
  Position a, b;
  Line() {}
  Line(Position a, Position b): a(a), b(b) {
    if (b < a) swap(a, b); // a < b
  }
  bool dot() const { return a == b; }
  bool operator==(const Line &l) const {
    return a == l.a && b == l.b;
  }
  Line operator&(const Line &l) const {
    Line none({INF, INF}, {INF, INF});
    Position c = l.a;
    Position d = l.b;

    if (dot()) {
      if (l.dot()) {
        if (a == l.a) {
          return (*this);
        }
        return none;
      }
      return l & (*this);
    }
    if (l.dot()) {
      if (ccw(a, b, c) == 0) {
        if (c < a || b < c) return none;
        return Line(c, c);
      }
      return none;
    }
    
    int ab = ccw(a, b, c)*ccw(a, b, d);
    int cd = ccw(c, d, a)*ccw(c, d, b);
    if (ab == 0 && cd == 0) {
      if (c <= b && a <= d) {
        return Line(max(a, c), min(b, d));
      }
      return none;
    }
    if (ab <= 0 && cd <= 0) {
      if (b.y < a.y) return l & (*this);
      lld b1 = a.y - a.x;
      lld b2 = c.x + c.y;
      if ((b2 - b1) % 2 == 1) return none;
      lld nx = (b2 - b1) / 2;
      lld ny = nx + b1;
      return Line({nx, ny}, {nx, ny});
    }
    return none;
  }
};

struct Group {
  vector<Line> lines;
  Group() {}
  void add_lines(Position o, lld dist) {
    Position a = {o.x - dist, o.y};
    Position b = {o.x, o.y + dist};
    Position c = {o.x + dist, o.y};
    Position d = {o.x, o.y - dist};
    lines.emplace_back(a, b);
    if (dist == 0) return;
    lines.emplace_back(b, c);
    lines.emplace_back(d, c);
    lines.emplace_back(a, d);
  }
  Group(Position o, lld d) {
    add_lines(o, d);
  }
  Group operator*(const Group& g) const {
    Group res;
    for (auto l: lines) {
      for (auto r: g.lines) {
        Line n = l & r;
        if (n.a.x == INF) continue;
        bool f = true;
        if (n.dot()) {
          for (auto p: res.lines) {
            if (p.dot() && n.a == p.a) {
              f = false;
              break;
            }
          }
        }
        if (f) res.lines.push_back(n);
      }
    }
    return res;
  }
};

int main(void)
{
  int n;
  scanf("%d", &n);
  Group ans;
  for (int i = 0; i < n; i++) {
    lld x, y, d;
    scanf("%lld%lld%lld", &x, &y, &d);
    // x *= 2; y *= 2; d *= 2;
    if (i == 0) ans = Group({x, y}, d);
    else ans = ans * Group({x, y}, d);
  }
  if (ans.lines.size() == 0) {
    puts("impossible");
    return 0;
  }

  bool all_same = true;
  for (int i = 0; i < ans.lines.size(); i++) {
    if (!ans.lines[i].dot() || !(ans.lines[i] == ans.lines[0])) {
      all_same = false;
      break;
    }
  }

  if (all_same) {
    Position p = ans.lines[0].a;
    printf("%lld %lld\n", p.x, p.y);
  } else {
    puts("uncertain");
  }
}
