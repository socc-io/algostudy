#include <bits/stdc++.h>
using namespace std;

int a, b, c, d, p;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> a >> b >> c >> d >> p;
  cout << min(a*p, b + max(0, (p-c) * d));
}
