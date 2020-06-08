#include <bits/stdc++.h>
using namespace std;
 
typedef pair<int, int> pi;
 
int n;
pi items[500];
pi sorted[500];
 
bool solve() {
  cin >> n;
  bool exist_zero = false;
  bool exist_one  = false;
  for (int i = 0; i < n; i++) cin >> items[i].first;
  for (int i = 0; i < n; i++) cin >> items[i].second;
  for (int i = 0; i < n; i++) {
    if (items[i].second) exist_one = true;
    else exist_zero = true;
  }
  if (exist_zero && exist_one) return true;
  for (int i = 1; i < n; i++) {
    if (items[i-1].first > items[i].first) return false;
  }
  return true;
}
 
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t;
  while (t--) {
    cout << (solve() ? "Yes" : "No") << '\n';
  }
}