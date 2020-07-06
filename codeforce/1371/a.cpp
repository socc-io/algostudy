#include <bits/stdc++.h>
using namespace std;

int solve(int n) {
  return (n+1)>>1;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    cout << solve(n) << '\n';
  }
}
