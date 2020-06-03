#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mod = 1000000;

int n;
string s;
ll mem[5001];
ll dp(int pos) {
	ll &ret = mem[pos];
	if (ret != -1) return ret;
	if (pos == n) return ret = 1;
	ret = 0;
	if (s[pos] == 0) return ret;
	if (n - pos >= 2) {
		int v = s[pos]*10 + s[pos+1];
		if (v <= 26) ret = (ret + dp(pos+2)) % mod;
	}
	ret = (ret + dp(pos+1)) % mod;
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> s;
	n = s.size();
	for (char &ch: s) ch -= '0';
	memset(mem, 0xff, sizeof(mem));
	cout << dp(0) << '\n';
}
