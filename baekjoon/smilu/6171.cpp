#include <set>
#include <algorithm>
using namespace std;

typedef long long ll;

#define LLONG_MAX 0x7fffffffffffffff

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	const ll inf = LLONG_MAX;
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
} lc;

#include <cstdio>
#include <vector>
using namespace std;

typedef long long ll;

int n;

struct land {
  ll a, b;
  bool operator<(const land &o) const {
    if (a == o.a) return b > o.b;
    return a > o.a;
  }
} ls[50001];

int main(void)
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++) scanf("%lld%lld", &ls[i].a, &ls[i].b);
  sort(ls, ls+n);

  ll now = -1;
  ll prev = 0;

  for (int i = 0; i < n; i++) {
    if (now >= ls[i].b) continue;
    now = ls[i].b;
    lc.add(-ls[i].a, -prev);
    prev = -lc.query(ls[i].b);
  }

  printf("%lld\n", prev);
}
