#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;

const int dd[4][2] = {
  {-1,0},{1,0},{0,-1},{0,1}
};

int n, m;
char tile[51][51];

bool block_badguy(int x, int y) {
  for (int di = 0; di < 4; di++) {
    int nx = x + dd[di][0], ny = y + dd[di][1];
    if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
         if (tile[nx][ny] == '.') tile[nx][ny] = '#';
    else if (tile[nx][ny] == 'G') return false;
    else if (tile[nx][ny] == 'B') continue;
    else if (tile[nx][ny] == '#') continue;
  }
  return true;
}

vector<vector<int>> check_reachable(int x, int y) {
  queue<pi> q;
  vector<vector<int>> dist(n, vector<int>(m, 0x3f3f3f3f));
  if (tile[x][y] == 'B' || tile[x][y] == '#') return dist;
  dist[x][y] = 0;
  q.push({x, y});
  while (!q.empty()) {
    auto u = q.front(); q.pop();
    int ux = u.first, uy = u.second;
    for (int di = 0; di < 4; di++) {
      int vx = ux + dd[di][0], vy = uy + dd[di][1];
      if (vx < 0 || vx >= n || vy < 0 || vy >= m) continue;
      if (dist[vx][vy] != 0x3f3f3f3f) continue;
      char vch = tile[vx][vy];
      if (vch != '.' && vch != 'G') continue;
      dist[vx][vy] = dist[ux][uy] + 1;
      q.push({vx, vy});
    }
  }
  return dist;
}

bool solve() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> tile[i];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (tile[i][j] == 'B') {
        if (!block_badguy(i, j)) return false;
      }
    }
  }
  auto dist = check_reachable(n-1, m-1);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (tile[i][j] == 'G') {
        if (dist[i][j] == 0x3f3f3f3f) return false;
      }
    }
  }
  return true;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t;
  while (t--) cout << (solve() ? "Yes" : "No") << '\n';
}
