#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;

int ccw(pi a, pi b, pi c) {
  int op = a.first*b.second + b.first*c.second + c.first*a.second;
  op -= (a.second*b.first + b.second*c.first + c.second*a.first);
  if (op > 0) return 1;
  else if (op == 0) return 0;
  else return -1;
}

int is_intersect(pair<pi, pi> x, pair<pi, pi> y) {
  pi a = x.first, b = x.second, c = y.first, d = y.second;
  int ab = ccw(a, b, c) * ccw(a, b, d);
  int cd = ccw(c, d, a) * ccw(c, d, b);
  return ab < 0 && cd < 0;
}

int main() {
  pi a, b, c, d;
  cin >> a.first >> a.second;
  cin >> b.first >> b.second;
  cin >> c.first >> c.second;
  cin >> d.first >> d.second;
  cout << is_intersect({a, b}, {c, d}) << '\n';
}
