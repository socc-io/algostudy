#include <cstdio>

int check(int a, int b, int c) {
  if (a+b+c != 180) return -1;
  if (a == b && b == c) return 3;
  if (a == b) return 2;
  if (a == c) return 2;
  if (b == c) return 2;
  return 1;
}

int main(void)
{
  int a, b, c; scanf("%d%d%d", &a, &b, &c);
  int res = check(a, b, c);
  if (res == -1) puts("Error");
  else if (res == 1) puts("Scalene");
  else if (res == 2) puts("Isosceles");
  else if (res == 3) puts("Equilateral");
}