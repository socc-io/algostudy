#include <bits/stdc++.h>
using namespace std;

int main(void)
{
  int cnt[10] = {0, };
  int n;
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n;
  for (int i = 0; i < n; i++) {
    int tmp; cin >> tmp;
    cnt[tmp/10]++;
    cnt[tmp%10]++;
  }
  unsigned long long ans = 1;
  for (int i = 0; i < 10; i++) {
    if (cnt[i] & 1) {
      ans = 0;
      break;
    }
    for (int j = cnt[i] - 1; j > 1; j -= 2) {
      ans *= j; 
    }
  }
  cout << ans << '\n';
}
