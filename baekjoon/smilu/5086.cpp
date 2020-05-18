#include <cstdio>

int main(void)
{
  while (1) {
    int a, b; scanf("%d%d", &a, &b);
    if (a == 0 && b == 0) break;
    if ((a%b) == 0) puts("multiple");
    else if ((b%a) == 0) puts("factor");
    else puts("neither");
  }
}
