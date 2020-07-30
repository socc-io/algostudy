#include <bits/stdc++.h>
using namespace std;

struct Query{
	int i, s, e, k;
	bool operator<(const Query &q) const { return s < q.s; }
};

struct Item{
	int s, e, v;
	bool operator<(const Item &e) const { return s < e.s; }
};

const int inf = 0x3f3f3f3f;

int n, q;
Item ts[1010];
Query qs[1000010];
int dp[100010];
bool ans[1000010];

int main(){
  ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++){
    cin >> ts[i].v >> ts[i].s >> ts[i].e;
	}
	cin >> q;
	for (int i = 0; i < q; i++){
    cin >> qs[i].s >> qs[i].k >> qs[i].e;
		qs[i].i = i;
		qs[i].e += qs[i].s;
	}
  sort(ts+1, ts+n+1);
	sort(qs, qs+q);
	fill(dp + 1, dp + 100001, -inf);
	dp[0] = inf;
	int p = 0;
	for (int i = 1; i <= n; i++){
		while (p < q && qs[p].s < ts[i].s){
			if (dp[qs[p].k] > qs[p].e) ans[qs[p].i] = 1;
			p++;
		}
		for (int j = 100000; j >= ts[i].v; j--){
			dp[j] = max(dp[j], min(dp[j - ts[i].v], ts[i].e));
		}
	}
	while (p < q){
		if (dp[qs[p].k] > qs[p].e) ans[qs[p].i] = 1;
		p++;
	}
	for (int i = 0; i < q; i++) puts(ans[i] ? "TAK" : "NIE");
}