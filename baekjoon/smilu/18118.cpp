#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, m;
ll dp[10][100000];
ll pw[19];

void solve() {
  cin >> n >> m;
  memset(dp, 0xFF, sizeof(dp));
  for (int i = 0; i < 10; i++) dp[0][i%m] = max(dp[0][i%m], (ll)i);
  dp[0][11%m] = max(dp[0][11%m], 11ll);
  for (int i = 0; i < n-1; i++) {
    int ni = i + 1;
    for (int j = 0; j < m; j++) {
      for (int k = 0; k < 10; k++) {
        ll nv = dp[i][j] * 10 + k;
        ll nj = nv % m;
        dp[ni][nj] = max(dp[ni][nj], nv);
      }
      ll nv = dp[i][j] * 100 + 11;
      ll nj = nv % m;
      dp[ni][nj] = max(dp[ni][nj], nv);
    }
  }
  cout << dp[n-1][0] << '\n';
}

int main() {
  pw[0] = 1;
  for (int i = 1; i < 19; i++) pw[i] = pw[i-1] * 10;
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t;
  while (t--) solve();
}
