#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll mod = 1000000000;

ll dp[10][10][100][10];

ll get_dp(int f, int t, int idx, int v) {
	if (idx < 0) return 0;
	if (f > t) return 0;
	if (v < f || v > t) return 0;
	ll &ret = dp[f][t][idx][v];
	if (ret != -1) return ret;
	if (v == f) {
		return ret = (get_dp(f  , t, idx-1, v+1)
		            + get_dp(f+1, t, idx-1, v+1)) % mod;
	}
	if (v == t) {
		return ret = (get_dp(f, t  , idx-1, v-1)
		            + get_dp(f, t-1, idx-1, v-1)) % mod;
	}
	return ret = (get_dp(f, t, idx-1, v+1)
	            + get_dp(f, t, idx-1, v-1)) % mod;
}

int main(void)
{
	memset(dp, 0xff, sizeof(dp));
	int n; scanf("%d", &n);
	for (int i = 1; i < 10; i++) {
		dp[i][i][0][i] = 1;
	}
	ll ans = 0;
	for (int i = 0; i < 10; i++) {
		ans += get_dp(0, 9, n-1, i);
		// printf("%d: %lld\n", i, get_dp(0, 9, n-1, i));
	}
	printf("%lld\n", ans % mod);
}
