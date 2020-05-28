#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll mod = 1000000007;

ll fac[4000001];

ll inv(ll a) {
  int p = mod-2;
  ll ret = 1;
  while (p) {
    if ((p & 1)) {
      ret = (ret*a)%mod;
    }
    a = (a*a)%mod;
    p >>= 1;
  }
  return ret;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  fac[0] = 1;
  for (int i = 1; i < 4000001; i++) {
    fac[i] = (fac[i-1]*i)%mod;
  }

  int m; cin >> m;
  for (int i = 0; i < m; i++) {
    int a, b; cin >> a >> b;
    cout << fac[a] * inv(fac[a-b]) % mod * inv(fac[b]) % mod << '\n';
  }
}
