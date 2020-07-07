#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  double h, w; cin >> h >> w;
  if (h > w) swap(h, w);
  double p1 = min(w/3, h);
  double p2 = min(w/2, h/2);
  cout << max(p1, p2);
}
