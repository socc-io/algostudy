#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll mod = 1000000007;

ll pow(ll a, ll b) {
	ll res = 1;
	while (b) {
		if ((b & 1)) {
			res = (res * a) % mod;
		}
		a = (a * a) % mod;
		b >>= 1;
	}
	return res;
}

inline ll inv(ll x) {
	return pow(x, mod-2);
}

inline ll add(ll a, ll b) {
	return (a + b) % mod;
}

inline ll mul(ll a, ll b) {
	return (a * b) % mod;
}

int n;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	ll ans = 0;
	for (int i = 0; i < n; i++) {
		ll a, b; cin >> a >> b;
		ans = add(ans, mul(b, inv(a)));
	}
	cout << ans << endl;
}
