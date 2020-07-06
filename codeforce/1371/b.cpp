#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll solve(ll n, ll r) {
  if (n <= r) return ((n * (n - 1)) >> 1) + 1;
  return (r*(r+1))>>1;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t;
  while (t--) {
    ll n, r; cin >> n >> r;
    cout << solve(n, r) << '\n';
  }
}
