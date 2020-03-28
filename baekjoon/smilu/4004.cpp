#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long lld;

#define EPS 1e-10

double dd[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

double llf_equal(double a, double b) {
  return a - EPS <= b && b <= a + EPS;
}

struct Kunai {
  double x, y;
  double vx, vy;
  double dead_time;
  void input() {
    int d; scanf("%lf%lf%d", &x, &y, &d);
    vx = dd[d][0]; vy = dd[d][1];
    dead_time = 0.0;
  }
};

struct Collision {
  double t;
  int a, b;
  Collision() {}
  Collision(double t, int a, int b): t(t), a(a), b(b) {}
  bool operator<(const Collision& b) const { return t < b.t; }
};

Kunai k[100000];
vector<Collision> c;
int n, w, h;

int main(void)
{
  scanf("%d%d%d", &w, &h, &n);
  for (int i = 0; i < n; i++) k[i].input();
  for (int i = 0; i < n; i++) { // check all possible collisions
    for (int j = i; j < n; j++) {
      Kunai ak = k[i], bk = k[j];
      double t, t2;
      if (ak.vx == bk.vx) { // vx parallel
        if (ak.vy == bk.vy) continue; // vx, vy parallel
        if (ak.x == bk.x) { // x always same
          t = (ak.y - bk.y) / (bk.vy - ak.vy);
          if (t > 0) c.emplace_back(t, i, j);
        }
        continue;
      } else if (ak.vy == bk.vy) { // vy parallel
        if (ak.y == bk.y) { // y always same
          t = (ak.x - bk.x) / (bk.vx - ak.vx);
          if (t > 0) c.emplace_back(t, i, j);
        }
        continue;
      }
      t = (ak.x - bk.x) / (bk.vx - ak.vx);
      if (t <= 0) continue;
      t2 = (ak.y - bk.y) / (bk.vy - ak.vy);
      if (llf_equal(t, t2)) {
        c.emplace_back(t, i, j);
      }
    }
  }
  sort(c.begin(), c.end()); // sort with time
  for (Collision co: c) {
    Kunai &ak = k[co.a], &bk = k[co.b];
    if (ak.dead_time != 0.0 && bk.dead_time == 0.0) { // only b alive
      if (llf_equal(ak.dead_time, co.t)) bk.dead_time = co.t;
    } else if (ak.dead_time == 0.0 && bk.dead_time != 0.0) { // only a alive
      if (llf_equal(bk.dead_time, co.t)) ak.dead_time = co.t;
    } else if (ak.dead_time == 0.0 && bk.dead_time == 0.0) { // both alive
      ak.dead_time = co.t;
      bk.dead_time = co.t;
    }
  }
  lld ans = 0;
  for (int i = 0; i < n; i++) {
    ans += floor(k[i].dead_time);
  }
  printf("%lld\n", ans);
}
