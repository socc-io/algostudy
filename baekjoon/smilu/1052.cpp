#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<int> get_bits(ll v) {
  vector<int> ret;
  for (int i = 0; i < 63; i++) {
    if (v & (1ll << i)) ret.push_back(i);
  }
  return ret;
}

int solve() {
  ll n; cin >> n;
  int k; cin >> k;
  ll m = n;
  while (1) {
    auto bits = get_bits(m);
    if (bits.size() <= k) return m - n;
    m += (1 << bits[0]);
  }
  return m - n;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << solve();
}
