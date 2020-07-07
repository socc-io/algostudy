#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll solve(ll x, ll k) {
  for (const ll l: {
    7 * k,
    3 * k + (k >> 1),
    1 * k + (k >> 1) + (k >> 2),
  }) if (x >= l) return l;
  return 0;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  ll x, k; cin >> x >> k;
  cout << solve(x * 1000, k * 1000);
}
