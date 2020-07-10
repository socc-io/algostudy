#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const ll ll_inf = 0x7fffffffffffffff;

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	const ll inf = ll_inf;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) { x->p = inf; return false; }
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
    k *= -1;
    m *= -1;
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		auto l = *lower_bound(x);
		return -(l.k * x + l.m);
	}
};

int n;
vector<pair<ll, int>> adj[100010];
int par[100010];
int sz[100010];
int in[100010];
int top[100010];
int cnum[100010], c_piv;
ll dp[100010];
ll dist[100010];
ll prep[100010];
ll mult[100010];
vector<LineContainer> lcs;

void init_sz(int u, int p) {
  sz[u] = 1;
  for (auto &e: adj[u]) if (e.second != p) {
    const int v = e.second;
    dist[v] = dist[u] + e.first;
    par[v] = u;
    init_sz(v, u);
    sz[u] += sz[v];
    if (sz[v] > sz[adj[u][0].second]) swap(e, adj[u][0]);
  }
}

void init_hld(int u, int p) {
  int piv = in[u] + 1;
  for (auto e: adj[u]) if (e.second != p) {
    const int v = e.second;
    in[v] = piv;
    piv += sz[v];
    top[v] = (v == adj[u][0].second ? top[u] : v);
    if (top[v] == v) cnum[v] = ++c_piv;
    else cnum[v] = cnum[u];
    init_hld(v, u);
  }
}

void init_dp(int u, int p) {
  int cur = top[u];
  ll min_local = ll_inf;
  while (1) {
    LineContainer &lc = lcs[cnum[cur]];
    if (!lc.empty()) {
      const ll local = lc.query(mult[u]);
      min_local = min(min_local, local);
    }
    if (cur == 0) break;
    cur = top[par[cur]];
  }
  if (min_local == ll_inf) min_local = 0;
  dp[u] = prep[u] + dist[u]*mult[u] + min_local;
  lcs[cnum[top[u]]].add(-dist[u], dp[u]);
  for (auto it = adj[u].rbegin(); it != adj[u].rend(); it++) {
    const auto e = *it;
    const int v = e.second;
    if (v == p) continue;
    init_dp(v, u);
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n;
  for (int i = 1; i < n; i++) {
    int a, b;
    ll w;
    cin >> a >> b >> w;
    adj[a].push_back({w, b});
    adj[b].push_back({w, a});
  }
  for (int i = 2; i <= n; i++) {
    cin >> prep[i] >> mult[i];
  }
  init_sz(1, 0);
  init_hld(1, 0);
  lcs.resize(c_piv + 1);
  init_dp(1, 0);
  for (int i = 2; i <= n; i++) {
    cout << dp[i];
    if (i < n) cout << ' ';
  }
}
