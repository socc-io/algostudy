#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  ll k, w, m; cin >> k >> w >> m;
  cout << (w - k + m - 1) / m;
}
