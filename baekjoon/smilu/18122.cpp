#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1000000007;

ll pw(ll a, int b) {
  ll ret = 1;
  while (b) {
    if (b&1) ret = (ret*a)%mod;
    a = (a*a)%mod;
    b >>= 1;
  }
  return ret;
}

int main() {
  int n; cin >> n;
  cout << pw(2,n+2)-5;
}
