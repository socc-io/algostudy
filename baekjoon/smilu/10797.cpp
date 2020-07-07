#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int d; cin >> d;
  int cnt = 0;
  for (int i = 0; i < 5; i++) {
    int t; cin >> t;
    cnt += (t % 10) == d;
  }
  cout << cnt;
}
