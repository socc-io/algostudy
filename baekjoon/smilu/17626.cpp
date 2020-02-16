#include <cstdio>

int cnt[50001];

void inspect(int n)
{
  int r = 123456789;
  for (int i = 1;; i++) {
    int p = n - i*i;
    if (p < 0) break;
    int v = cnt[p];
    if (v < r) r = v;
  }
  cnt[n] = r + 1;
}

int main(void)
{
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) inspect(i);
  printf("%d", cnt[n]);
}