#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

#define INF 0x7F7F7F7F7F7F7F7F

typedef long long lld;

int n;
lld dp[2001][2001], a[2001];

lld get(int i, int j) {
  lld &ans = dp[i][j];
  if (ans != INF) return ans;
  if (j == i - 1) {
    ans = get(i-1, 0);
    for (int x = 1; x < i - 1; x++) {
      ans = min(ans, get(i-1, x) + abs(a[i] - a[x]));
    }
  } else {
    ans = get(i-1, j) + abs(a[i] - a[i-1]);
  }
  return ans;
}

int main(void)
{
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%lld", a+i);
  memset(dp, 0x7F, sizeof(dp));
  lld ans = INF;
  dp[1][0] = 0;
  for (int i = 0; i < n; i++) {
    ans = min(ans, get(n, i));
  }
  printf("%lld\n", ans);
}
