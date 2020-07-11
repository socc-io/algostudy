#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n, m; cin >> n >> m;
  vector<bool> row(n);
  vector<bool> col(m);
  for (int i = 0; i < n; i++) {
    string s; cin >> s;
    for (int j = 0; j < m; j++) {
      const char ch = s[j];
      if (ch == 'X') {
        row[i] = true;
        col[j] = true;
      }
    }
  }
  const int cnt_row = count(row.begin(), row.end(), false);
  const int cnt_col = count(col.begin(), col.end(), false);
  cout << max(cnt_row, cnt_col);
}
