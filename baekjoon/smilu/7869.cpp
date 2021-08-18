#include <bits/stdc++.h>
using namespace std;

#define M_PI 3.14159265358979323846

double sqr(double x) { return x*x; }

double solve() {
	double x1, y1, r1, x2, y2, r2;
	cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
	double d2 = sqr(x1-x2) + sqr(y1-y2);
	double d = sqrt(d2);
	double r12 = sqr(r1), r22 = sqr(r2);
	
	if (sqr(r1 + r2) <= d2) return 0.0; // independent
	if (sqr(r1 - r2) >= d2) return M_PI * sqr(min(r1, r2)); // included
	
	double B = 2.0 * acos((d2 + r12 - r22) / (2.0*d*r1));
	double C = 2.0 * acos((d2 + r22 - r12) / (2.0*d*r2));
	
	return (r12 * (B - sin(B)) + r22 * (C - sin(C))) * 0.5;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout << fixed;
	cout.precision(3);
	cout << solve() << '\n';
}
