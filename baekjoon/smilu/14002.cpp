#include <bits/stdc++.h>
using namespace std;

int n;
int arr[1010];

int dp[1010];
int tk[1010];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n;
  for (int i = 0; i < n; i++) cin >> arr[i];
  dp[0] = 1;
  tk[0] = 0;
  for (int i = 1; i < n; i++) {
    dp[i] = 1;
    tk[i] = i;
    for (int j = 0; j < i; j++) {
      if (arr[j] >= arr[i]) continue;
      if (dp[j] + 1 > dp[i]) {
        dp[i] = dp[j] + 1;
        tk[i] = j;
      }
    }
  }

  // cout << "dp: "; for (int i = 0; i < n; i++) cout << dp[i] << ' '; cout << '\n';

  int mi = 0;
  for (int i = 1; i < n; i++) {
    if (dp[mi] < dp[i]) mi = i;
  }
  vector<int> ans;
  int cur = mi;
  while (tk[cur] != cur) {
    ans.push_back(arr[cur]);
    cur = tk[cur];
  }
  ans.push_back(arr[cur]);
  reverse(ans.begin(), ans.end());
  cout << ans.size() << '\n';
  for (int v: ans) cout << v << ' ';  cout << '\n';
}
