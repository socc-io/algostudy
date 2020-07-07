#include <bits/stdc++.h>
using namespace std;

inline int sqr(int v) { return v*v; }

int solve(const int a[3]) {
  if (sqr(a[0]) + sqr(a[1]) == sqr(a[2])) return 1;
  if (a[0] == a[1] && a[1] == a[2]) return 2;
  return 0;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int a[3]; cin >> a[0] >> a[1] >> a[2];
  sort(a, a+3);
  cout << solve(a);
}
