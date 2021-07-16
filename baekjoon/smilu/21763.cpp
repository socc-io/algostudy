#include <bits/stdc++.h>
using namespace std;

int n, k;

bool f(int x, int y) {
	if (x == 0) return y == 0;
	if (x == n-1) return y == n-1;
	return y == n-1-x;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> k;
	int th = n*(n-1) - (n==2);
	if (k > th) {
		puts("NO");
		return 0;
	}
	puts("YES");
	int cnt = k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (f(i, j) || cnt <= 0) putchar('.');
			else {
				putchar('#');
				--cnt;
			}
		}
		putchar('\n');
	}
}
