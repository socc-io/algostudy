#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

const ll INF = 0x3f3f3f3f3f3f3f3fll;

enum { LEFT, RIGHT };
enum { LU, LD, RU, RD };

struct Point {
  ll x, y;
  Point() {}
  Point(ll x, ll, y): x(x), y(y) {}
  void input() { scanf("%lld%lld", &x, &y); }
};

struct Event {
  Point p;
  int type;
  int par;
  Event() {}
  void init(const Line &line, bool left) {
  }
};

struct Line {
  Point l, r;
  int type;
  int next;
  Line() {}
  Line(const Point &l, const Point &r): l(l), r(r) {}
  void input() { l.input(); r.input(); }
  void update_type() {
    type = l.y < r.y ? LEFT : RIGHT;
  }
};

int n;
Line lines[100000];
Event events[200000];

void get_input() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) lines[i].input();
  ll sx; scanf("%lld", &sx);
  lines[n] = Line(Point(sx-1, INF), Point(sx, INF-1));
  ++n;
  
  for (int i = 0; i < n; i++) lines[i].update_type();
  
}

int main(void)
{
}
