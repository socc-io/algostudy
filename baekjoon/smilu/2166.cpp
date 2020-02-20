#include <cstdio>

typedef long long lld;

struct pos {
  lld x, y;
};

lld ccw(pos a, pos b, pos c) {
  lld p1 = (b.x - a.x) * (c.y - a.y);
  lld p2 = (b.y - a.y) * (c.x - a.x);
  return p1 - p2;
}

int n;
pos p[10000];

int main(void)
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%lld%lld", &p[i].x, &p[i].y);
  }
  lld res = 0;
  for (int i = 1; i < n-1; i++) {
    res += ccw(p[0], p[i], p[i+1]);
  }
  if (res < 0) res *= -1;

  printf("%lld.", res/2);
  printf("%d\n", res&1?5:0);
}
