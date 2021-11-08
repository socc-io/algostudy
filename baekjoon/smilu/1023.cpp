#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n;
ll dp[50][101][2];

ll get(int pos, int cnt, bool downed) {
	if (pos >= n) return downed || (cnt != n);
	ll &ret = dp[pos][cnt][downed];
	if (~ret) return ret;
	return ret =  get(pos + 1, cnt + 1, downed)
	            + get(pos + 1, cnt - 1, downed || cnt <= n);
}

void print(int pos, int cnt, bool downed, ll index) {
	if (pos >= n) return;
	ll pivot = get(pos + 1, cnt + 1, downed);
	if (index < pivot) {
		putchar('(');
		print(pos + 1, cnt + 1, downed, index);
	} else {
		putchar(')');
		print(pos + 1, cnt - 1, downed || cnt <= n, index - pivot);
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	memset(dp, 0xFF, sizeof(dp));
	ll k;
	cin >> n >> k;
	if (k >= get(0, n, false)) puts("-1");
	else print(0, n, false, k);
	return 0;
}
