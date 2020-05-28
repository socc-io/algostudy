#include <bits/stdc++.h>
using namespace std;

int s[500000];
int s_piv;

int main(void)
{
  ios::sync_with_stdio(0); cin.tie(0);
  int n; cin >> n;
  cin >> s[0];
  s_piv = 1;
  long long ans = 0;
  for (int i = 1; i < n; i++) {
    int h; cin >> h;
    auto it = lower_bound(s, s+s_piv, h, greater<int>());
    ans += s+s_piv-it+(it>s);
    while (s_piv && s[s_piv-1] < h) s_piv--;
    s[s_piv++] = h;
  }
  cout << ans << '\n';
}
