#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  vector<int> a(4); for (int &v: a) cin >> v;
  sort(a.begin(), a.end());
  cout << abs(a[0]+a[3]-a[1]-a[2]);
}
