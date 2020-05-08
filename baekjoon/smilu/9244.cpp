#include <cstdio>
#include <cassert>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

typedef long long ll;

enum { LEFT, RIGHT };
enum { RU, RD, LD, LU };

struct Point {
  ll x, y;
  Point() {}
  Point(ll x, ll y): x(x), y(y) {}
  void input() { scanf("%lld%lld", &x, &y); }
  Point operator-(const Point &p) const {
    return Point(x - p.x, y - p.y);
  }
  ll cross(const Point &p) const {
    return x * p.y - y * p.x;
  }
};

struct Line {
  Point l, r;
  int index;
  int type;
  void update_type() { type = l.y < r.y ? LEFT : RIGHT; }
  void input(int i) {
    l.input();
    r.input();
    if (l.x > r.x) swap(l, r);
    index = i;
    update_type();
  }
  ll below_x() { return type == LEFT ? l.x : r.x; }
  bool between(const Point &p) const { return l.x <= p.x && p.x <= r.x; }
  bool below(const Point &p) const { return (r - l).cross(p - l) < 0; }
  bool operator<(const Line &b) const {
    if (index == b.index) return false;
    if (between(b.l)) return below(b.l);
    if (b.between(l)) return !b.below(l);
    assert(false);
    return index < b.index;
  }
  bool operator==(const Line &b) const { return index == b.index; }
  Line() {}
  Line(int i, const Point &l, const Point &r): l(l), r(r), index(i) {
    update_type();
  }
};

struct Event {
  ll x;
  int type;
  int par;
  Event() {}
  void init(const Line &line, bool left) {
    par = line.index;
    x = left ? line.l.x : line.r.x;
    if (left) {
      type = line.type == LEFT ? LD : LU;
    } else {
      type = line.type == LEFT ? RU : RD;
    }
  }
  bool operator<(const Event &e) const {
    if (x == e.x) return type > e.type;
    return x < e.x;
  }
};

int n, en;
Line lines[100010];
Event events[200020];
int nxt[100010];

int main(void)
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++) lines[i].input(i);
  ll sx; scanf("%lld", &sx);
  lines[n] = Line(n, Point(sx-1, 1000002), Point(sx, 1000001));
  ++n; en = n<<1;
  for (int i = 0; i < n; i++) {
    events[ i<<1   ].init(lines[i], true);
    events[(i<<1)|1].init(lines[i], false);
  }
  sort(events, events + en);
  set<Line> scope;
  for (int i = 0; i < n; i++) nxt[i] = -2;
  for (int i = 0; i < en; i++) {
    const Event &e = events[i];
    Line &l = lines[e.par];
    // printf("event { x: %lld, l: (%lld,%lld), r: (%lld,%lld) }\n", e.x, l.l.x, l.l.y, l.r.x, l.r.y);
    if (e.type == LU) {
      scope.insert(l);
    } else if (e.type == LD) {
      scope.insert(l);
      auto it = scope.find(l); it++;
      nxt[l.index] = it == scope.end() ? -1 : it->index;
    } else if (e.type == RU) {
      scope.erase(l);
    } else { // RD
      auto it = scope.find(l); it++;
      nxt[l.index] = it == scope.end() ? -1 : it->index;
      scope.erase(l);
    }
  }
  int cur = n-1;
  while (nxt[cur] >= 0) cur = nxt[cur];
  assert(nxt[cur] != -2);
  printf("%lld\n", lines[cur].below_x());
}
