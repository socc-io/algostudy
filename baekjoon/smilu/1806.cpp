#include <cstdio>

#define INF 0x7FFFFFF0

int n, s;
int arr[100000];

int min(int a, int b) { return a < b ? a : b; }

int main(void)
{
  scanf("%d%d", &n, &s);
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }
  int b = 0, e = 0, t = 0, ans = INF;
  while (b <= e && e <= n) {
    if (t >= s) ans = min(ans, e-b);
    if (t <= s) t += arr[e++];
    if (t >  s) t -= arr[b++];
  }
  printf("%d", ans == INF ? 0 : ans);
}