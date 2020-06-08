#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pi;

int n;
int as[400004];
pi bs[200002];
int point[200002];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n;
  for (int i = 0; i < n; i++) cin >> as[i];
  for (int i = 0; i < n; i++) cin >> bs[i].first;
  for (int i = 0; i < n; i++) bs[i].second = i;
  sort(bs, bs+n);
  for (int i = 0; i < n; i++) {
    auto it = lower_bound(bs, bs+n, make_pair(as[i], 0));
    as[i] = it->second + 1;
  }
  // for (int i = 0; i < n; i++) cout << as[i] << ' '; cout << '\n';
  for (int i = 0; i < n; i++) as[n+i] = as[i];
  n <<= 1;
  // for (int i = 0; i < n; i++) cout << as[i] << ' '; cout << '\n';
  for (int i = 0; i < n; i++) as[i] = i+1-as[i]+1;
  // for (int i = 0; i < n; i++) cout << as[i] << ' '; cout << '\n';

  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (as[i] < 1) continue;
    if (as[i] > n/2) continue;
    point[as[i]]++;
    ans = max(ans, point[as[i]]);
  }

  cout << ans << '\n';
}
