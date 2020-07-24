#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n;
int lev[5001];
int min_i[5001];
int max_i[5001];

void skip(int n) {
  int tmp;
  while (n--) cin >> tmp;
}

ll comb(ll a, ll b) {
  b = min(b, a-b);
  ll ans = 1;
  for (ll i = 0; i < b; i++) {
    ans *= a-i;
    ans /= i+1;
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> lev[i];
    skip(lev[i]);
  }
  sort(lev, lev+n);
  memset(min_i, 0x3f, sizeof(min_i));
  for (int i = 0; i < n; i++) {
    min_i[lev[i]] = min(min_i[lev[i]], i);
    max_i[lev[i]] = max(max_i[lev[i]], i);
  }
  ll bs = 0, gs = accumulate(lev, lev+n, 0);
  ll ans = 0;
  for (int i = 0; i < n-1; i++) {
    bs += lev[i];
    gs -= lev[i];
    const ll k = n-i-1;
    if (gs == bs + k*(k-1)) {
      ans += comb(max_i[lev[i]] - min_i[lev[i]] + 1, i - min_i[lev[i]] + 1);
    }
  }
  cout << ans << '\n';
}
