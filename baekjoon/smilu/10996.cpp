#include <cstdio>

void stripe(int n) {
  static const char st_chs[2] = {'*', ' '};
  ++n;
  n &= ~1;
  --n;
  for (int i = 0; i < n; i++) putchar(st_chs[i&1]);
}

void line(int n, int i) {
  if (i & 1) stripe(n);
  else {
    putchar(' ');
    stripe(n-1);
  } puts("");
}

int main(void)
{
  int n; scanf("%d", &n);
  for (int i = 1; i <= 2*n; i++) line(n, i);
}