#include <cstdio>

int main(void)
{
  int a, b, c, d;
  scanf("%d%d%d%d", &a, &b, &c, &d);
  int t = a*3600+b*60+c+d;
  printf("%d %d %d\n", t/3600%24, t/60%60, t%60);
}
