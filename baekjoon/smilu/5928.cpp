#include <cstdio>

const int st = 11*1440+11*60+11;

int main() {
  int a, b, c; scanf("%d%d%d", &a, &b, &c);
  int t = a*1440+b*60+c;
  int dt = t - st;
  if (dt < 0) puts("-1");
  else printf("%d\n", dt);
}
