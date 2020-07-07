#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  ll a, b, k; cin >> a >> b >> k;
  ll ak = a / k;
  ll bk = b / k;
  
  ll outer = ak * bk;
  ll inner = (ak > 2 && bk > 2) ? (ak-2) * (bk-2) : 0;
  cout << outer - inner;
}
