#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

bool solve(ll v, ll c, ll n, ll m) {
  if (v+c < n+m) return false;
  if (min(v,c) < m) return false;
  return true;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t;
  while (t--) {
    ll a, b, n, m; cin >> a >> b >> n >> m;
    cout << (solve(a, b, n, m) ? "Yes" : "No") << '\n';
  }
}
