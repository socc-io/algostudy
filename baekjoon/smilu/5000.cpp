#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

const int MAX_N = 100010;

struct BIT {
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
	int n; cin >> n;
	vector<int> a(n);
	vector<pi> b(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) {
		cin >> b[i].first;
		b[i].second = i + 1;
	}
	sort(b.begin(), b.end());
	ll cnt = 0;
	for (int i = 0; i < n; i++) {
		a[i] = lower_bound(b.begin(), b.end(), make_pair(a[i], -1))->second;
		cnt += bit.query(a[i] + 1, n);
		bit.update(a[i], 1);
	}
	cout << ((cnt & 1) ? "Impossible" : "Possible") << '\n';
}

// 4 2 1 3
