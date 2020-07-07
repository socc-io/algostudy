#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int a, b, c, d, e, f; cin >> a >> b >> c >> d >> e >> f;
  cout << (a+b+c+d-min(a,min(b,min(c,d))))+max(e,f);
}
