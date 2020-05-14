#include <cstdio>

int main(void)
{
  int a, b, c;
  scanf("%d%d%d", &a, &b, &c);
  int t = a*60+b+c;
  printf("%d %d\n", t/60%24, t%60);
}
