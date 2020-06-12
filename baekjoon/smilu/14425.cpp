#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  set<string> s;
  int n, m; cin >> n >> m;
  for (int i = 0; i < n; i++) {
    string tmp; cin >> tmp;
    s.insert(tmp);
  }
  int cnt = 0;
  for (int i = 0; i < m; i++) {
    string tmp; cin >> tmp;
    cnt += s.find(tmp) != s.end();
  }
  cout << cnt << '\n';
}
