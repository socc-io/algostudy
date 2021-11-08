#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
typedef pair<i64, i64> pi;

const i64 i64_inf = 0x7fffffffffffffff;

int n;
array<i64, 32> cost;
array<i64, 32> value;
int k;
i64 money;

vector<pi> perm(int from, int to) {
	vector<pi> ret;
	ret.reserve(1 << (to - from));
	ret.emplace_back(0, 0);
	int phi = 1;
	for (int i = from; i < to; i++) {
		for (int j = 0; j < phi; j++) {
			ret.emplace_back(
				ret[j].first  + value[i],
				ret[j].second + cost[i]
			);
		}
		phi <<= 1;
	}
	return ret;
}

int main() {
	int t;
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; i++) cin >> cost[i];
	for (int i = 0; i < n; i++) cin >> value[i];
	cin >> k >> t;
	for (int i = 0; i < t; i++) {
		int idx; cin >> idx;
		money += cost[idx];
	}
	vector<pi> A = perm(0, n>>1);
	vector<pi> B = perm(n>>1, n);
	sort(B.begin(), B.end());
	for (int i = B.size() - 2; i >= 0; i--)
		B[i].second = min(B[i].second, B[i+1].second);
	i64 ans = i64_inf;
	for (auto &a: A) {
		pi tg = make_pair(k - a.first, 0);
		auto lo = lower_bound(B.begin(), B.end(), tg);
		if (lo != B.end()) ans = min(ans, a.second + lo->second);
	}
	printf("%lld", ans == i64_inf ? -1 : max(ans - money, 0ll));
}
