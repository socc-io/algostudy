#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t;
  int a = t / 300;
  t -= a * 300;
  int b = t / 60;
  t -= b * 60;
  int c = t / 10;
  t -= c * 10;
  if (t != 0) {
    cout << "-1";
    return 0;
  }
  cout << a << ' ' << b << ' ' << c;
}
