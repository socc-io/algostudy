#include <bits/stdc++.h>
using namespace std;

int n, m;
char b[51][51];
int s[51][51];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) cin >> b[i];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			b[i][j] = (b[i][j] == 'W' ? 1 : 0);
			if (((i + j) & 1)) b[i][j] = !b[i][j];
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			s[i][j] = s[i][j-1] + s[i-1][j] - s[i-1][j-1] + b[i-1][j-1];
		}
	}
	int ans = 0x3f3f3f3f;
	for (int i = 0; i <= n-8; i++) {
		for (int j = 0; j <= m-8; j++) {
			int k = i + 8, l = j + 8;
			int sum = s[k][l] - s[k][j] - s[i][l] + s[i][j];
			int loc = min(sum, 64 - sum);
			ans = min(ans, loc);
		}
	}
	cout << ans << '\n';
}
