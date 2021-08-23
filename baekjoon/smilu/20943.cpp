#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

int n;
pair<int, int> ss[500500];

int gcd(int a, int b) {
	if (a < b) return gcd(b, a);
	while (b) {
		int tmp = a % b;
		a = b;
		b = tmp;
	}
	return a;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		int g = gcd(a, b);
		a /= g;
		b /= g;
		if (a < 0) {
			a *= -1;
			b *= -1;
		}
		ss[i] = {a, b};
	}
	sort(ss, ss + n);
	
	ll ans = n;
	ans *= ans - 1;
	ans >>= 1;
	int begin = 0;
	for (int i = 1; i <= n; i++) {
		if (i >= n || ss[i-1] != ss[i]) {
			ll sz = i - begin;
			ans -= (sz * (sz - 1)) >> 1;
			begin = i;
		}
	}
	
	cout << ans;
}