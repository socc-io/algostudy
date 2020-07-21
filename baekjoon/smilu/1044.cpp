#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pl;

ll as[36];
ll bs[36];
vector<pl> L[19];

ll min_diff = 0x3f3f3f3f3f3f3f3f;
ll min_lr;

void update(ll diff, ll lr) {
  if (diff < min_diff) {
    min_diff = diff;
    min_lr = lr;
  } else if (diff == min_diff) {
    min_lr = min(min_lr, lr);
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n; cin >> n;
  const int n2 = n >> 1;
  for (int i = 0; i < n; i++) cin >> as[i];
  for (int i = 0; i < n; i++) cin >> bs[i];

  const ll div_end = 1 << n2;
  for (ll div = 0; div < div_end; div++) {
    ll l = 0;
    int cnt_bit = 0;
    for (int i = 0; i < n2; i++) {
      if (div & (1ll << (n2-1-i))) {
        l -= bs[i];
        ++cnt_bit;
      }
      else l += as[i];
    }
    L[cnt_bit].emplace_back(l, div);
  }
  for (int i = 1; i < n2; i++) sort(L[i].begin(), L[i].end());

  for (ll div = 0; div < div_end; div++) {
    ll r = 0;
    int cnt_bit = 0;
    for (int i = 0; i < n2; i++) {
      if (div & (1ll << (n2-1-i))) {
        r -= bs[n2 + i];
        ++cnt_bit;
      }
      else r += as[n2 + i];
    }
    const auto &ls = L[n2 - cnt_bit];
    auto l = lower_bound(ls.begin(), ls.end(), make_pair(-r, -1ll));
    if (l != ls.end()) update(l->first + r, (l->second << n2) | div);
    if (l != ls.begin()) {
      --l;
      l = lower_bound(ls.begin(), ls.end(), make_pair(l->first, -1ll));
      update(-(l->first + r), (l->second << n2) | div);
    }
  }
  
  for (int i = 0; i < n; i++) {
    cout << (char)('1' + ((min_lr & (1ll << (n-1-i))) > 0)) << ' ';
  }
}
