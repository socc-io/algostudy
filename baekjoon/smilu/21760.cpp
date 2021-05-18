#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n, m, k, d;

ll solve() {
  cin >> n >> m >> k >> d;
  ll p = (k*n*m*(m-1) + n*m*m*(n-1)) >> 1;
  ll a = d/p*p;
  return a - (a == 0);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t;
  while (t--) {
    cout << solve() << '\n';
  }
}

