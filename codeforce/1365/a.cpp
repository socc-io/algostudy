#include <bits/stdc++.h>
using namespace std;

int n, m;
int cell[50][50];
int row[50];
int col[50];

bool solve() {
  cin >> n >> m;
  memset(row, 0x00, sizeof(row));
  memset(col, 0x00, sizeof(col));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> cell[i][j];
      if (cell[i][j] == 1) {
        row[i] = 1;
        col[j] = 1;
      }
    }
  }
  auto is_positive = [](int a){ return a > 0; };
  auto cnt_row = n - count_if(row, row+n, is_positive);
  auto cnt_col = m - count_if(col, col+m, is_positive);
  auto cnt = min(cnt_row, cnt_col);

  // cout << cnt_row << ' ' << cnt_col << '\n';

  return !(cnt & 1);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t;
  while (t--) {
    cout << (solve() ? "Vivek" : "Ashish") << '\n';
  }
}
