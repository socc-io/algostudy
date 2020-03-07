#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define INF 0x7FFFFFF0

int n;
int h[50];
int dp[50][500000];

int get(int i, int d) {
  if (i < 0 || i > 50) return -INF;
  if (d < 0 || d >= 500000) return -INF;

  if (i == n && d == 0) return 0;
  if (i == n && d > 0) return -INF;

  int &ret = dp[i][d];
  if (ret != -1) return ret;

  ret = -INF;
  ret = max(ret, get(i + 1, d));
  ret = max(ret, get(i + 1, d + h[i]));
  if (h[i] > d) ret = max(ret, get(i + 1, h[i] - d) + d);
  else ret = max(ret, get(i + 1, d - h[i]) + h[i]);

  return ret;
}

int main(void)
{
  memset(dp, -1, sizeof(dp));
  scanf("%d", &n);
  for (int i = 0; i < n; i++) scanf("%d", &h[i]);
  int mh = get(0, 0);
  printf("%d", mh ? mh : -1);
}
