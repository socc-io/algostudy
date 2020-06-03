#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;

const int dd[4][2] = {{-1,0},{1,0},{0,1},{0,-1}};

int n, m;
int tile[50][50];
vector<pi> spots;

int experiment(const vector<bool> &flags) {
  vector<vector<int>> dist(n, vector<int>(n, 0x3f3f3f3f));
  queue<pi> q;
  for (int i = 0; i < spots.size(); i++) {
    if (flags[i] == false) continue;
    int x = spots[i].first, y = spots[i].second;
    q.push(spots[i]);
    dist[x][y] = 0;
  }
  while (!q.empty()) {
    auto u = q.front(); q.pop();
    int nd = dist[u.first][u.second] + 1;
    for (int di = 0; di < 4; di++) {
      int nx = u.first + dd[di][0];
      int ny = u.second + dd[di][1];
      if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
      if (tile[nx][ny] == 1) continue;
      if (nd < dist[nx][ny]) {
        dist[nx][ny] = nd;
        q.push({nx, ny});
      }
    }
  }
  int ret = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (tile[i][j] == 1) continue;
      ret = max(ret, dist[i][j]);
    }
  }
  return ret;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> tile[i][j];
      if (tile[i][j] == 2) {
        spots.push_back({i, j});
      }
    }
  }
  vector<bool> comb(spots.size());
  for (int i = 0; i < min((int)spots.size(), m); i++) {
    comb[spots.size()-1-i] = true;
  }
  int ans = 0x3f3f3f3f;
  do {
    ans = min(ans, experiment(comb));
  } while(next_permutation(comb.begin(), comb.end()));
  cout << (ans == 0x3f3f3f3f ? -1 : ans) << '\n';
}
