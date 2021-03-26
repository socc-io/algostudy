#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAX_N = 1000010;

int n, m, k;

struct bit_point_update_range_query {
  ll ft[MAX_N];
  void update(int x, ll v) {
    for (int i = x; i <= MAX_N; i+=(i&-i)) ft[i] += v;
  }
  ll query(int x) {
    ll ret = 0;
    for (int i = x; i > 0; i-=(i&-i)) ret += ft[i];
    return ret;
  }
  ll query(int a, int b) {
    return query(b) - query(a-1);
  }
} bit;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		ll v; cin >> v;
		bit.update(i, v);
	}
	for (int i = 0; i < m+k; i++) {
		ll c, p, q; cin >> c >> p >> q;
		if (c == 1) {
			bit.update(p, q - bit.query(p, p));
		} else {
			cout << bit.query(p, q) << '\n';
		}
	}
}
