#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int a, b, c, d,
      e, f, g, h;
  cin >> a >> b >> c >> d >> e >> f >> g >> h;
  const int dx = max(c, g) - min(a, e);
  const int dy = max(d, h) - min(b, f);
  const int r = max(dx, dy);
  cout << r*r;
}
