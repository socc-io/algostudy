#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;

const int dd[4][2] = {
  {-1,0},{1,0},{0,1},{0,-1}
};

int n, m, nm;
char tile[101][101];
char buf[111];

pi decompose(int index) {
  return {index / m, index % m};
}

int compose(int x, int y) {
  return x*m + y;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> m >> n; nm = n * m;
  for (int i = 0; i < n; i++) {
    cin >> tile[i];
  }
  priority_queue<pi, vector<pi>, greater<pi>> pq;
  vector<int> dist(nm, 0x3f3f3f3f);
  vector<bool> vis(nm);
  dist[0] = 0;
  pq.push({0, 0});
  while (!pq.empty()) {
    auto t = pq.top(); pq.pop();
    int ui = t.second;
    if (vis[ui]) continue;
    vis[ui] = true;
    auto u = decompose(ui);
    int ux = u.first, uy = u.second;
    int ud = t.first;
    for (int di = 0; di < 4; di++) {
      int vx = ux + dd[di][0], vy = uy + dd[di][1];
      int vi = compose(vx, vy);
      if (vx < 0 || vx >= n || vy < 0 || vy >= m) continue;
      int vd = ud + (tile[vx][vy] - '0');
      if (vd < dist[vi]) {
        dist[vi] = vd;
        pq.push({vd, vi});
      }
    }
  }

  // for (int i = 0; i < n; i++) {
  //   for (int j = 0; j < m; j++) {
  //     cout << dist[compose(i, j)] << ',';
  //   } cout << '\n';
  // }

  cout << dist[compose(n-1, m-1)] << '\n';
}
