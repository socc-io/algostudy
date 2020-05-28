#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll mod = 1000000007ll;

int n;
ll sp[300000];
ll pow2[300000];

int main() {
  pow2[0] = 1;
  for (int i = 1; i < 300000; i++) {
    pow2[i] = (pow2[i-1]<<1)%mod;
  }

  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n;
  for (int i = 0; i < n; i++) cin >> sp[i];
  sort(sp, sp+n);
  ll ans = 0;
  for (int i = 1; i < n; i++) {
    ans += sp[i]*(pow2[i]-1);
    ans %= mod;
  }
  for (int i = 0; i < n-1; i++) {
    ans -= sp[i]*(pow2[n-i-1]-1);
    ans %= mod;
  }
  if (ans < 0) ans += mod;
  cout << ans << '\n';
}
