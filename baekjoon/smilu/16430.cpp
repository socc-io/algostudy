#include <cstdio>

int gcd(int a, int b) {
  while (b) {
    int t = a%b;
    a = b;
    b = t;
  }
  return a;
}

int main(void)
{
  int a, b; scanf("%d%d", &a, &b);
  a = b-a;
  int g = gcd(b, a);
  printf("%d %d\n", a/g, b/g);
}
