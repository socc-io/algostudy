#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

#define LL_MAX 0x7fffffffffffffff

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	const ll inf = LL_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) { x->p = inf; return false; }
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
  pair<ll, ll> query_line(ll x) {
		auto l = *lower_bound(x);
		return {l.k, l.m};
  }
};

ll solve(const vector<ll> &arr) {
  const int n = arr.size();
  vector<ll> dp(n);
  vector<ll> sm(n);  
  LineContainer lc;

  // printf("arr: "); for (int i = 0; i < n; i++) printf("%3lld ", arr[i]); puts("");

  sm[0] = arr[0];
  for (int i = 1; i < n; i++) sm[i] = sm[i-1] + arr[i];

  lc.add(arr[0], arr[0]);
  ll ans = -LL_MAX;
  for (int i = 1; i < n; i++) {
    auto line = lc.query_line(i);
    ll k = line.first, m = line.second;
    dp[i] = k*i + m;

    ans = max(ans, dp[i] - sm[i]);
    lc.add(arr[i], sm[i-1]+arr[i]*(1-i));
  }

  // printf("dp : "); for (int i = 0; i < n; i++) printf("%3lld ", dp[i]); puts("");

  return ans + sm[n-1];
}

int main(void)
{
  ll ans0, ans1;
  int n; scanf("%d", &n);
  vector<ll> arr(n);
  for (int i = 0; i < n; i++) {
    ll tmp; scanf("%lld", &tmp);
    arr[i] = tmp;
  }
  ans0 = solve(arr);
  reverse(arr.begin(), arr.end());
  ans1 = solve(arr);
  printf("%lld\n%lld\n", ans1, ans0);
}
