#include <bits/stdc++.h>
using namespace std;

int n, l;
int tile[101][101];
int t_tile[101][101];

bool CheckLine(int * arr) {
	vector<bool> f(n, false);
	
	for (int i = 1; i < n; i++) {
		if (arr[i] == arr[i-1]) continue;
		if (arr[i] == arr[i-1] + 1) {
			for (int j = 0; j < l; j++) {
				if (i-1-j < 0 || f[i-1-j]) return false;
				if (arr[i-1-j] != arr[i-1]) return false;
				f[i-1-j] = true;
			}
		} else if (arr[i] == arr[i-1] - 1) {
			for (int j = 0; j < l; j++) {
				if (i+j >= n || f[i+j]) return false;
				if (arr[i+j] != arr[i]) return false;
				f[i+j] = true;
			}
		} else return false;
	}
	
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n >> l;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> tile[i][j];
			t_tile[j][i] = tile[i][j];
		}
	}
	
	int ans = 0;
	for (int i = 0; i < n; i++) {
		ans += CheckLine(tile[i]);
		ans += CheckLine(t_tile[i]);
	}
	
	cout << ans << '\n';
	
	return 0;
}
