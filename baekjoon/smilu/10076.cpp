#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> p;

#define INF 0x7fffffffffffffff

struct CHT{
	ll a[101010], b[101010], c[101010];
	int pv, top;

	void clear(){
		pv = top = 0;
	}

	ll f(ll idx, ll x){
		return a[idx]*x + b[idx];
	}

	void insert(ll aa, ll bb, ll cc){
		if(top >= 1 && aa == a[top-1]){
			c[top-1] = cc; return;
		}
		while(top >= 2 && (b[top-1] - b[top-2]) * (a[top-2] - aa) >= (bb - b[top-2]) * (a[top-2] - a[top-1])) top--;
		a[top] = aa;
		b[top] = bb;
		c[top] = cc;
		top++;
		if(pv >= top) pv = top - 1;
	}

	p query(ll x){
		while(pv+1 < top && a[pv+1]*x + b[pv+1] > a[pv]*x + b[pv]) pv++;
		return {f(pv, x), c[pv]};
	}
} lc;

int max_n, max_k;
ll arr[100010];
ll sum[100010];

ll dp[2][100010];
int piv;
int pn[201][100010];

void fill_dp() {
  for (int k = 1; k <= max_k; k++) {
    lc.clear();
    lc.insert(0, 0, 0);
    for (int n = 1; n <= max_n; n++) {
      auto res = lc.query(sum[n]);
      dp[piv][n] = res.first;
      pn[k][n] = res.second;
      // cout << pn[k][n] << ' ';
      ll si = sum[n];
      lc.insert(si, dp[1-piv][n] - si*si, n);
    }
    // cout << '\n';
    piv = 1 - piv;
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> max_n >> max_k;
  for (int i = 1; i <= max_n; i++) cin >> arr[i];
  for (int i = 1; i <= max_n; i++) sum[i] = sum[i-1] + arr[i];
  fill_dp();
  cout << dp[1-piv][max_n] << '\n';

  vector<ll> ans;
  ans.push_back(-1);
  int cur = max_n;
  for (int k = max_k; k >= 1; k--) {
    ans.push_back(pn[k][cur]);
    cur = pn[k][cur];
  }
  sort(ans.begin(), ans.end());
  for (int i = 1; i <= max_k; i++) {
    if (ans[i] == 0) ans[i] = 1;
    if (ans[i] <= ans[i-1]) ans[i] = ans[i-1] + 1;
  }
  for (int i = 1; i <= max_k; i++) cout << ans[i] << ' '; cout << '\n';
}
