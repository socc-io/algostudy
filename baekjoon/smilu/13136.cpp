#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  long long a, b, c; cin >> a >> b >> c;
  cout << ((a+c-1)/c)*((b+c-1)/c);
}
