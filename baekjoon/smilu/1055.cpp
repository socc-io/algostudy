#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll inf = 0x3f3f3f3fll;

ll d_count, c_count;
string inp, fmt;

ll len_cc[101];
ll length(ll level) {
	if (d_count == 1) return min(len_cc[0] + level*c_count, inf);
	if (level <= 0) return len_cc[0];
	level = min(level, 100ll);
	if (len_cc[level]) return len_cc[level];
	ll tmp = length(level - 1);
	tmp = tmp * d_count + c_count;
	return len_cc[level] = min(tmp, inf);
}

void print(int level, int f, int t) {
	if (level == 0) {
		t = min(t, (int)inp.size());
		while (f < t) putchar(inp[f++]);
		return;
	}
	
	int l = 0, r, s, e;
	for (char ch: fmt) {
		if (l >= t) break;
		if (ch == '$') {
			r = l + length(level - 1);
			s = max(l, f); e = min(r, t);
			if (s < e) print(level - 1, s - l, e - l);
			l = r;
		} else {
			if (f <= l && l < t) putchar(ch);
			l++;
		}
	}
}

char findch(int level, int pos) {
	if (level == 0) {
		if (pos < len_cc[0]) return inp[pos];
		return '-';
	}
	for (char ch: fmt) {
		if (ch == '$') {
			int l = length(level - 1);
			if (l <= pos) pos -= l;
			else return findch(level - 1, pos);
		} else {
			if (pos) pos--;
			else return ch;
		}
	}
	return '-';
}

int valid_n(int p2) {
	int i = 1;
	while (length(i) < p2) i <<= 1;
	return i;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	
	int n, p1, p2;
	cin >> inp >> fmt >> n >> p1 >> p2;
	
	for (char ch: fmt) {
		d_count += ch == '$';
	}
	c_count = fmt.size() - d_count;
	
	len_cc[0] = inp.size();
	
	if (d_count == 1) {
		for (int i = p1-1; i < (int)inp.size(); i++) putchar(inp[i]);
		for (int i = max((int)inp.size(), p1-1); i < p2; i++) {
			if (i >= length(n)) putchar('-');
			else putchar(fmt[1+((i-inp.size())%c_count)]);
		}
		return 0;
	}
	
	n = min(n, valid_n(p2));
	
	print(n, p1-1, p2);
	int i = p2 - max((int)length(n), p1-1);
	if (i > 0) while (i--) putchar('-');
	
	// for (int i = p1-1; i < p2; i++) putchar(findch(n, i));
}
