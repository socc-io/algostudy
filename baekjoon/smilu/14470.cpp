#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int a, b, c, d, e; cin >> a >> b >> c >> d >> e;
  cout << max(-a,0)*c + (a<0?d:0) + ((b-max(a,0))*e);
}
