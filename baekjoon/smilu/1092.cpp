#include <bits/stdc++.h>
using namespace std;

int n, m;
int cw[55];
int bw[10001];
int cs[55];

int solve() {
  cin >> n;
  for (int i = 0; i < n; i++) cin >> cw[i];
  sort(cw, cw + n);
  cin >> m;
  for (int i = 0; i < m; i++) cin >> bw[i];
  sort(bw, bw+m, greater<int>());
  for (int i = 0; i < m; i++) {
    const int ci = lower_bound(cw, cw + n, bw[i]) - cw;
    if (ci == n) return -1;
    (*min_element(cs + ci, cs + n))++;
  }
  return *max_element(cs, cs+n);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << solve();
}
