#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class HashContainer {
  //1e9-63, 1e9+7, 1e9+9, 1e9+103
	//1e5+3, 1e5+13, 131071, 524287
  int n;
  ll mod;
  vector<ll> _hs;
  vector<ll> _bs;
public:
  HashContainer(const string &s, ll p, ll mod): mod(mod) {
    n = s.size();
    _hs = vector<ll>(n+1);
    for (int i = n-1; i >= 0; i--) {
      _hs[i] = (_hs[i+1] * p + s[i]) % mod;
    }
    _bs = vector<ll>(n+1);
    _bs[0] = 1, _bs[1] = p;
    for (int i = 2; i <= n; i++) {
      _bs[i] = _bs[i-1] * p % mod;
    }
  }
  ll substr(int l, int r) const {
    ll ret = _hs[l] - _hs[r+1] * _bs[r-l+1];
    ret %= mod; ret += mod; ret %= mod;
    return ret;
  }
};

bool check(
  const HashContainer &hc1,
  const HashContainer &hc2,
  const int n,
  const int m,
  const int q
) {
  if (hc1.substr(q-m, q-1) != hc1.substr(n-m, n-1)) return false;
  return hc2.substr(q-m, q-1) == hc2.substr(n-m, n-1);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  string s; cin >> s;
  const int n = (int)s.size();
  
  HashContainer hc1(s, 1e9-63, 131071);
  HashContainer hc2(s, 1e9+9 , 524287);

  int m; cin >> m;
  while (m--) {
    int q; cin >> q;
    int l = 0, r = q;
    while (l < r) {
      const int m = (l + r + 1) >> 1;
      if (check(hc1, hc2, n, m, q)) {
        l = m;
      } else {
        r = m-1;
      }
      // cout << l << ' ' << r << '\n';
    }
    cout << l << '\n';
  } 
}
