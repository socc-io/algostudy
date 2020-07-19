#include <bits/stdc++.h>
using namespace std;

const int dd[8][2] = {
  {-1,-1},{-1,0},{-1,1},
  {0,-1},{0,1},
  {1,-1},{1,0},{1,1}
};

int n, m;
int tile[100][100];
int grp[100][100], grp_piv;
vector<pair<int, int>> memb[10000];

void group(int x, int y, int gi) {
  // cout << '(' << x << ", " << y << "), ";
  grp[x][y] = gi;
  memb[gi].push_back(make_pair(x, y));
  for (int i = 0; i < 8; i++) {
    const int nx = x + dd[i][0], ny = y + dd[i][1];
    if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
    if (tile[nx][ny] != tile[x][y]) continue;
    if (grp[nx][ny] != 0) continue;
    group(nx, ny, gi);
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> tile[i][j];
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grp[i][j] != 0) continue;
      // cout << "group(" << grp_piv + 1 << "): ";
      group(i, j, ++grp_piv);
      // cout << '\n';
    }
  }
  int cnt = 0;
  for (int i = 1; i <= grp_piv; i++) {
    bool flag = false;
    for (auto xy: memb[i]) {
      const int x = xy.first, y = xy.second;
      for (int j = 0; j < 8; j++) {
        const int nx = x + dd[j][0], ny = y + dd[j][1];
        if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
        if (grp[nx][ny] == i) continue;
        if (tile[nx][ny] > tile[x][y]) {
          flag = true;
          break;
        }
      }
      if (flag) break;
    }
    if (!flag) ++cnt;
  }
  cout << cnt << '\n';
}
