#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const double inf = DBL_MAX;

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

double f(double bp) {
    double max_x = max_lc_x.query(bp);
    double min_x = min_lc_x.query(bp);
    double max_y = max_lc_y.query(bp);
    double min_y = min_lc_y.query(bp);
    return max(max_x + min_x, max_y + min_y);
}

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

    double low = 0;
    double high = 2000;
    for (int i = 0; i < 100 && low < high; i++) {
        double a = (low * 2 + high) / 3;
        double b = (low + 2 * high) / 3;
        if (f(a) < f(b)) {
            high = b;
        } else {
            low = a;
        }
    }
    
    printf("%.11lf\n", f(low));

    return 0;
}
