#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int zo = 5000000;

int n, s;
int arr[40];
ll dp[2][2*zo + 1];
int t = 0;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> s;
	for (int i = 0; i < n; i++) cin >> arr[i];
	// sort(arr, arr + n);
	dp[t][zo] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= 2 * zo; j++) {
			int dst = j - arr[i];
			if (dst < 0 || dst > 2 * zo) continue;
			dp[1-t][j] = dp[t][dst] + dp[t][j];
		}
		t = 1 - t;
	}
	ll ans = dp[t][s + zo] - (s == 0);
	cout << ans << endl;
}
