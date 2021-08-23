#include <bits/stdc++.h>
using namespace std;

int main() {
	int n; cin >> n;
	
	long long ans = 0;
	int i;
	for (i = 1; i*i <= n-1; i++) {
		ans += ((n-1)/i);
	}
	i--;
	ans = n + (ans << 1) - i*i;
	
	cout << ans << '\n';
}
