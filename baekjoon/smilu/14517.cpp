#include <cstdio>
#include <cstring>

#define MOD 10007

typedef long long lld;

char s[1001];
lld dp[1001][1001];

int main(void) {
  scanf("%s", s);
  int n = strlen(s);
  for (int i = 0; i < n; i++) {
    dp[i][i] = 1;
    dp[i][i+1] = s[i] == s[i+1] ? 3 : 2;
  }
  for (int L = 2; L < n; L++) {
    for (int l = 0; l < n; l++) {
      int r = l + L;
      if (r > n) break;
      dp[l][r] = dp[l+1][r] + dp[l][r-1] - dp[l+1][r-1] + MOD;
      if (s[l] == s[r]) {
        dp[l][r] += dp[l+1][r-1] + 1;
      }
      dp[l][r] %= MOD;
    }
  }
  printf("%lld\n", dp[0][n-1]);
}
