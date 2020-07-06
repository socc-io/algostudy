#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int row_sum(const vector<vector<bool>> &tile, int ri) {
  int ret = 0;
  for (int i = 0; i < tile.size(); i++) ret += tile[ri][i];
  return ret;
}

int col_sum(const vector<vector<bool>> &tile, int ci) {
  int ret = 0;
  for (int i = 0; i < tile.size(); i++) ret += tile[i][ci];
  return ret;
}

inline ll sqr(ll v) { return v*v; }

void solve(int n, int k) {
  vector<vector<bool>> tile(n, vector<bool>(n));
  int x = 0, y = 0;
  for (int i = 0; i < k; i++) {
    if (i > 0 && i % n == 0) ++y;
    tile[x][y] = true;
    ++x;
    ++y;
    x %= n;
    y %= n;
  }

  int min_rs = 0x3f3f3f3f;
  int max_rs = 0;
  int min_cs = 0x3f3f3f3f;
  int max_cs = 0;
  for (int i = 0; i < n; i++) {
    int rs = row_sum(tile, i);
    min_rs = min(min_rs, rs);
    max_rs = max(max_rs, rs);
    int cs = col_sum(tile, i);
    min_cs = min(min_cs, cs);
    max_cs = max(max_cs, cs);
  }

  ll fv = sqr(max_rs - min_rs) + sqrt(max_cs - min_cs);
  cout << fv << '\n';
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << tile[i][j];
    } cout << '\n';
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t;
  while (t--) {
    int n, k; cin >> n >> k;
    solve(n, k);
  }
}
