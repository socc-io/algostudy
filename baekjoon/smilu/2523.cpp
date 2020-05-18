#include <cstdio>

void dot(int n) {
  for (int i = 0; i < n; i++) putchar('*');
  puts("");
}

int main(void)
{
  int n; scanf("%d", &n);
  for (int i = 1; i <= n; i++) dot(i);
  for (int i = n-1; i >= 1; i--) dot(i);
}
