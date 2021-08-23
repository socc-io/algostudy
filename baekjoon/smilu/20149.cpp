#include <bits/stdc++.h>
using namespace std;

#define X first
#define Y second

typedef long long ll;
typedef pair<ll, ll> pll;

int ccw(pll a, pll b, pll c) {
  ll op = a.first*b.second + b.first*c.second + c.first*a.second;
  op -= (a.second*b.first + b.second*c.first + c.second*a.first);
  if (op > 0) return 1;
  else if (op == 0) return 0;
  else return -1;
}

pair<double, double> get_intersection(pll a, pll b, pll c, pll d) {
	double p1 = a.X*b.Y - a.Y*b.X;
	double p2 = c.X*d.Y - c.Y*d.X;
	double q1 = p1 * (c.X - d.X) - (a.X - b.X) * p2;
	double q2 = p1 * (c.Y - d.Y) - (a.Y - b.Y) * p2;
	double dv  = (a.X - b.X) * (c.Y - d.Y) - (a.Y - b.Y) * (c.X - d.X);
	
	if (dv == 0) {		
		if (a > b) swap(a, b);
		if (c > d) swap(c, d);
		if (b == c && a <= c) return b;
		else if (a == d && c <= a) return a;
		return make_pair(1234.0, 1234.0);
	}
	
	return make_pair(q1 / dv, q2 / dv);
}

int is_intersect(pll a, pll b, pll c, pll d) {
  int ab = ccw(a, b, c)*ccw(a, b, d);
  int cd = ccw(c, d, a)*ccw(c, d, b);
  if (ab == 0 && cd == 0) {
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);
    return c <= b && a <= d;
  }
  return ab <= 0 && cd <= 0;
}

int main() {
  pll a, b, c, d;
  cin >> a.first >> a.second;
  cin >> b.first >> b.second;
  cin >> c.first >> c.second;
  cin >> d.first >> d.second;
  cout.precision(9);
  if (is_intersect(a, b, c, d)) {
	  cout << "1\n";
	  auto res = get_intersection(a, b, c, d);
	  if (res.first != 1234.0 || res.second != 1234.0) {
		  cout << fixed;
		  cout.precision(9);
		  cout << res.first << ' ' << res.second << '\n';
	  }
  } else {  
	cout << "0\n";
  }
}
