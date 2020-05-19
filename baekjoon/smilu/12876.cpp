#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll LL_INF = 0x7fffffffffffffff;

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	const ll inf = LL_INF;
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
    if (empty()) return -LL_INF;
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

struct Seg {
  LineContainer lc[1200000];
  void add(int n, int s, int e, int f, int t, ll lk, ll lm) {
    if (t < s || e < f) return;
    if (f <= s && e <= t) {
      // printf("add %lld, %lld in %d, %d\n", lk, lm, s, e);
      lc[n].add(lk, lm);
      return;
    }
    int m = (s+e)>>1, l = n<<1, r = l|1;
    add(l,s,m,f,t,lk,lm);
    add(r,m+1,e,f,t,lk,lm);
  }
  ll query(int n, int s, int e, int x, ll lx) {
    ll now = lc[n].query(lx);
    if (s == e) return now;
    int m = (s+e)>>1, l = n<<1, r = l|1;
    if (x <= m) return max(now, query(l,s,m,x,lx));
    else return max(now, query(r,m+1,e,x,lx));
  }
} seg;

struct LineCache {
  ll k, m;
  int f, t;
} lines[300000];
int line_piv;
int line_indices[300000];

ll query_xs[300000];
int query_t[300000];
int query_piv;

int main(void)
{
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int type; scanf("%d", &type);
    if (type == 1) {
      ll k, m; scanf("%lld%lld", &k, &m);
      line_indices[i] = line_piv;
      lines[line_piv++] = {k, m, i, n-1};
    } else if (type == 2) {
      int ri; scanf("%d", &ri);
      lines[line_indices[ri-1]].t = i-1;
    } else if (type == 3) {
      ll x; scanf("%lld", &x);
      query_t[query_piv] = i;
      query_xs[query_piv++] = x;
    }
  }
  for (int i = 0; i < line_piv; i++) {
    const auto &line = lines[i];
    seg.add(1,0,n-1,line.f,line.t,line.k,line.m);
  }
  for (int i = 0; i < query_piv; i++) {
    int t = query_t[i];
    ll x = query_xs[i];
    ll v = seg.query(1,0,n-1,t,x);
    if (v == -LL_INF) puts("EMPTY");
    else printf("%lld\n", v);
  }
}
