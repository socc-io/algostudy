#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;

const int L_INF = 0x3f3f3f3f;

const pi op_mul = {0, '*'};
const pi op_div = {0, '/'};

bool is_digit(char ch) {
	return '0' <= ch && ch <= '9';
}

bool is_op(char ch) {
	return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

pi find_bracket(const string &s, int start = 0) {
	int cur = start;
	while (cur < s.size() && s[cur] != '(') ++cur;
	if (cur == s.size()) return {-1, -1};
	int beg = cur;
	int lev = 0;
	while (cur < s.size()) {
		     if (s[cur] == '(') ++lev;
		else if (s[cur] == ')') --lev;
		if (lev == 0) break;
		++cur;
	}
	if (cur == s.size()) return {-1, -1};
	return {beg, cur + 1};
}

pi parse_int(const string &s, int start = 0) {
	int ret = 0;
	int cur = start;
	while (is_digit(s[cur])) {
		ret = ret*10 + (s[cur] - '0');
		++cur;
	}
	// cout << "parsed: " << ret << '\n';
	return {ret, cur};
}

int calculate_items(const vector<pi> &items) {
	vector<pi> stk;
	for (const auto &i: items) {
		stk.push_back(i);
		auto M = stk[stk.size()-2];
		if (M == op_mul || M == op_div) {
			auto L = stk[stk.size()-3];
			auto R = stk[stk.size()-1];
			int val;
			     if (M == op_mul) val = L.second * R.second;
			else if (M == op_div) val = L.second / R.second;
			stk[stk.size()-3] = {1, val};
			stk.pop_back();
			stk.pop_back();
		}
	}
	assert(stk[0].first == 1);
	int ret = stk[0].second;
	for (int i = 1; i < stk.size(); i += 2) {
		char op = stk[i].second;
		int R = stk[i+1].second;
		     if (op == '+') ret += R;
		else if (op == '-') ret -= R;
	}
	return ret;
}

int calculate(const string &s, int start, int end) {
	// cout << "calculate: " << s.substr(start, end-start) << '\n';
	vector<pi> items;
	bool turn = true;
	for (int cur = start; cur != end;) {
		char ch = s[cur];
		if (turn) {
			if (is_op(ch) || ch == ')') return L_INF;
			if (ch == '(') {
				pi bracket = find_bracket(s, cur);
				int val = calculate(s, cur+1, bracket.second-1);
				if (val == L_INF) return L_INF;
				items.push_back({1, val});
				cur = bracket.second;
			} else {
				pi parsed = parse_int(s, cur);
				items.push_back({1, parsed.first});
				cur = parsed.second;
			}
		} else {
			if (!is_op(ch)) return L_INF;
			items.push_back({0, ch});
			++cur;
		}
		turn = !turn;
	}
	if (items.back().first == 0) return L_INF;
	return calculate_items(items);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	string s; cin >> s;
	int ret = calculate(s, 0, s.size());
	if (ret == L_INF) cout << "ROCK\n";
	else cout << ret << '\n';
}
