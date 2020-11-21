#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const double inf = 9999999999999;

struct Line {
	mutable double k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(double x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	double div(double a, double b) { return a / b; }
	bool isect(iterator x, iterator y) {
		if (y == end()) { x->p = inf; return false; }
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(double k, double m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	double query(double x) const {
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

int n;
LineContainer max_lc_x, min_lc_x, max_lc_y, min_lc_y;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        int px, py, vx, vy;
        cin >> px >> py >> vx >> vy;
        max_lc_x.add(vx, px);
        max_lc_y.add(vy, py);
        min_lc_x.add(-vx, -px);
        min_lc_y.add(-vy, -py);
    }

    vector<double> bps;
    for (auto & it: max_lc_x) bps.push_back(it.p);
    for (auto & it: max_lc_y) bps.push_back(it.p);
    for (auto & it: min_lc_x) bps.push_back(it.p);
    for (auto & it: min_lc_y) bps.push_back(it.p);
    sort(bps.begin(), bps.end());
    bps.erase(unique(bps.begin(), bps.end()), bps.end());
    bps.erase(bps.begin(), lower_bound(bps.begin(), bps.end(), 0));
    
    double ans = inf;
    for (double bp: bps) {
        double max_x = max_lc_x.query(bp);
        double min_x = -min_lc_x.query(bp);
        double max_y = max_lc_y.query(bp);
        double min_y = -min_lc_y.query(bp);
        double local = max(max_x - min_x, max_y - min_y);
        ans = min(ans, local);
    }

    printf("%.9lf\n", ans);
}
