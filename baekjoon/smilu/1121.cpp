#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;

typedef long long lld;

int n, k;
int a[50];

lld comb(lld a, lld b) {
  lld res = 1;
  if (a - b < b) b = a - b;
  for (int i = 0; i < b; i++) res *= a-i;
  for (int i = 0; i < b; i++) res /= i+1;
  return res;
}

// a[r1, n)에서 r2개를 뽑아서 합했을 때 r3 이하인 경우의 수
int _dp[50][11][50001];
int dp(int r1, int r2, int r3) {
  if (r3 <  0) return 0;
  if (r2 == 0) return 1;
  if (r1 >= n) return 0;

  int &res = _dp[r1][r2][r3];
  if (res != -1) return res;

  return res = dp(r1 + 1, r2 - 1, r3 - a[r1])
            +  dp(r1 + 1, r2, r3);
}

int main(void)
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
  scanf("%d", &k);

  sort(a, a + n, greater<int>());

  memset(_dp, 0xFF, sizeof(_dp));
  // printf("sizeof dp: %luMB\n", sizeof(_dp) / 1000000);

  lld ans = 0;
  for (int i = 0; i <= n-k; i++) {
    ans += comb(n-1-i, k-1) - dp(i+1, k-1, a[i]);
  }
  printf("%lld\n", ans);
}
