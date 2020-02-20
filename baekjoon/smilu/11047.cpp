#include <cstdio>

int n, k;
int a[10];

int main(void)
{
  int c = 0;
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  for (int i = n - 1; i >= 0; i--) {
    c += k / a[i];
    k %= a[i];
    if (k == 0) break;
  }
  printf("%d", c);
}