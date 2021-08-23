#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n;
int h[250010];
int x[250010];

const ll mod = 1000000007;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) cin >> h[i];
	
	memcpy(x, h, sizeof(x));
	for (int i = 0; i < n; i++) {
		if (i+1 <  n) x[i] = min(x[i], h[i+1]);
		if (i-1 >= 0) x[i] = min(x[i], h[i-1]);
	}
	ll ans = x[0];
	for (int i = 1; i < n; i++) {
		ans = (ans * x[i]) % mod;
	}
	cout << ans;
}
