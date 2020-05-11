#include <cstdio>

void dot(int n) {
  for (int i = 0; i < n; i++) putchar('*');
}

void spc(int n) {
  for (int i = 0; i < n; i++) putchar(' ');
}

void print(int lev, int x) {
  int n = 4*lev-3;
  if (x == 1 || x == n) {
    dot(n);
  } else if (x == 2 || x == n-1) {
    dot(1); spc(n-2); dot(1);
  } else {
    dot(1); spc(1);
    print(lev-1, x-2);
    spc(1); dot(1);
  }
}

int main(void)
{
  int n; scanf("%d", &n);
  int h = 4*n-3;
  for (int i = 1; i <= h; i++) {
    print(n,i); puts("");
  }
}
