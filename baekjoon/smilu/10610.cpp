#include <bits/stdc++.h>
using namespace std;

char s[100001];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> s;
	int n = strlen(s);
	sort(s, s+n, greater<char>());
	int sum = 0;
	for (int i = 0; i < n; i++) sum += s[i] - '0';
	if (sum % 3 != 0 || s[n-1] != '0') {
		cout << "-1";
	} else {
		cout << s;
	}
}
