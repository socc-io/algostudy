#include <bits/stdc++.h>
using namespace std;

struct Message {
	int left;
	int sender;
} msg[10000];

int n, m, q;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> q;
	for (int i = 0; i < m; i++) {
		char ch; cin >> msg[i].left >> ch;
		msg[i].sender = ch - 'A';
		// cout << "msg " << i << ": " << msg[i].left << ' ' << msg[i].sender << '\n';
	}
	if (msg[q-1].left == 0) {
		cout << "-1\n";
		return 0;
	}
	int b_set = 1;
	for (int i = 0; i < m; i++) {
		if (msg[i].left < msg[q-1].left) continue;
		b_set |= 1 << msg[i].sender;
	}
	for (int i = 0; i < n; i++) {
		if ((b_set & (1<<i)) == 0) cout << (char)('A' + i) << ' ';
	}
}
