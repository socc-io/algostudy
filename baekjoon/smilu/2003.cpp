#include <cstdio>

int n, m, a[10000];

int main(void)
{
  int s = 0, ans = 0;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
  for (int i = 0, j = 0; i < n; i++) {
    s += a[i];
    while (s > m && j < n) s -= a[j++];
    ans += (s == m);
  }
  printf("%d\n", ans);
}
