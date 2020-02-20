#include <cstdio>

int n;
int vs[100000][2];
int dp[100001][2];

int max(int a, int b) { return a > b ? a : b; }
void inspect(int i) {
  dp[i][0] = max(dp[i-1][1], dp[i-2][1]) + vs[i][0];
  dp[i][1] = max(dp[i-1][0], dp[i-2][0]) + vs[i][1];
}

void solve() {
  scanf("%d", &n);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &vs[j][i]);
    }
  }
  dp[0][0] = vs[0][0];
  dp[0][1] = vs[0][1];
  dp[1][0] = vs[1][0] + vs[0][1];
  dp[1][1] = vs[1][1] + vs[0][0];
  for (int i = 2; i < n; i++) {
    dp[i][0] = max(dp[i-1][1], dp[i-2][1]) + vs[i][0];
    dp[i][1] = max(dp[i-1][0], dp[i-2][0]) + vs[i][1];
  }
  printf("%d\n", max(dp[n-1][0], dp[n-1][1]));
}

int main(void)
{
  int t;
  scanf("%d", &t);
  while(t--) solve();
}
