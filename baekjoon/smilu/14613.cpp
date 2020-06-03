#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll perm(int a, int b) {
	ll ret = 1;
	for (int i = 0; i < b; i++) ret *= a-i;
	return ret;
}

ll comb(int a, int b) {
	if (a-b < b) b = a-b;
	return perm(a, b)/perm(b, b);
}

double pw, pl, pd;
double pn[41];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> pw >> pl >> pd;
	for (int nd = 0; nd <= 20; nd++) {
		for (int nw = 0; nw <= 20-nd; nw++) {
			int nl = 20-nd-nw;
			ll cn = comb(20,nd)*comb(20-nd,nw);
			double pp = pow(pw,nw)*pow(pl,nl)*pow(pd,nd);
			pn[nw-nl+20] += pp*cn;
		}
	}
	cout << fixed;
	cout.precision(8);
	for (int i = 0; i < 4; i++) {
		double sum = 0;
		for (int j = 0; j < 10; j++) {
			sum += pn[i*10+j];
		}
		cout << sum << '\n';
	}
	cout << pn[40] << '\n';
}
