#include <cstdio>
int main(void)
{
  int a, b; scanf("%d%d", &a, &b);
  if ((a+b)&1 || a < b) {
    puts("-1"); return 0;
  }
  printf("%d %d\n", (a+b)/2, (a-b)/2);
}