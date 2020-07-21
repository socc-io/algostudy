#include <bits/stdc++.h>
using namespace std;

int dp[51][51];

int try_str(const string &s) {
  const int n = s.size();
  for (int i = 0; i < n-1; i++) {
    dp[i][i+1] = s[i] != s[i+1];
  }
  for (int l = 2; l < n; l++) {
    for (int i = 0, j = l; j < n; i++, j++) {
      dp[i][j] = min(
        min(dp[i+1][j], dp[i][j-1]) + 1,
        dp[i+1][j-1] + (s[i] != s[j])
      );
    }
  }
  return dp[0][n-1];
}

int solve() {
  string s; cin >> s;
  int ans = try_str(s);
  for (int i = 0; i < s.size(); i++) {
    for (int j = i+1; j < s.size(); j++) {
      if (s[i] == s[j]) continue;
      swap(s[i], s[j]);
      ans = min(ans, try_str(s) + 1);
      swap(s[i], s[j]);
    }
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << solve() << '\n';
}
