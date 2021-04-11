#include <bits/stdc++.h>
using namespace std;

int n, c, hn;
int w[31];
vector<int> s1, s2;

void dfs(int s, int e, int sw, bool flag) {
  if (sw > c) return;
  if (s >= e) {
    (flag ? s1 : s2).push_back(sw);
    return;
  }
  dfs(s+1, e, sw + w[s], flag);
  dfs(s+1, e, sw, flag);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> c;
  hn = (n >> 1);
  for (int i = 0; i < n; i++) cin >> w[i];
  dfs(0, hn, 0, true);
  sort(s1.begin(), s1.end());
  dfs(hn, n, 0, false);
  sort(s2.begin(), s2.end());

  long long ans = 0;
  for (int i = 0, j = (s2.size() - 1); i < s1.size() && j >= 0; i++) {
    while (j >= 0 && s1[i] + s2[j] > c) --j;
    ans += j + 1;
  }

  cout << ans;
}
