#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;
typedef pair<int, pair<int, int> > edge;

const int dd[4][2] = {
  {-1,0},{1,0},{0,-1},{0,1},
};

int n, m;
int tile[11][11];
int grp[11][11];
int dist[11][11];
int max_grp;

struct UnionFind {
  int par[11];
  UnionFind() {
    iota(par, par+11, 0);
  }
  int getpar(int x) {
    return par[x] == x ? x : (par[x] = getpar(par[x]));
  }
  bool merge(int a, int b) {
    a = getpar(a);
    b = getpar(b);
    if (a == b) return false;
    par[a] = b;
    return true;
  }
} uf;

bool outbound(int x, int y) {
  return x < 0 || x >= n || y < 0 || y >= m;
}

void find_grp(int x, int y, int g) {
  grp[x][y] = g;
  for (int di = 0; di < 4; di++) {
    int nx = x + dd[di][0], ny = y + dd[di][1];
    if (outbound(nx, ny)) continue;
    if (!tile[nx][ny] || grp[nx][ny]) continue;
    find_grp(nx, ny, g);
  }
}

pi search(int x, int y, int dx, int dy, int w) {
  if (grp[x][y]) return make_pair(grp[x][y], w);
  int nx = x + dx, ny = y + dy;
  if (outbound(nx, ny)) return make_pair(-1, -1);
  return search(nx, ny, dx, dy, w+1);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  memset(dist, 0x3f, sizeof(dist));
  for (int i = 0; i < 10; i++) dist[i][i] = 0;
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> tile[i][j];
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (!tile[i][j] || grp[i][j]) continue;
      find_grp(i, j, ++max_grp);
    }
  }
  // printf("found %d islands\n", max_grp);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (!tile[i][j] || !grp[i][j]) continue;
      int u = grp[i][j];
      for (int di = 0; di < 4; di++) {
        int nx = i + dd[di][0], ny = j + dd[di][1];
        pi res = search(nx, ny, dd[di][0], dd[di][1], 0);
        int v = res.first, l = res.second;
        if (l < 2) continue;
        // printf("dist(%d, %d) = %d\n", u, v, l);
        dist[u][v] = min(dist[u][v], l);
        dist[v][u] = dist[u][v];
      }
    }
  }

  vector<edge> es;
  for (int i = 1; i <= max_grp; i++) {
    for (int j = i+1; j <= max_grp; j++) {
      int d = dist[i][j];
      if (d == 0x3f3f3f3f) continue;
      es.push_back(make_pair(d, make_pair(i, j)));
    }
  }
  sort(es.begin(), es.end());
  int ans = 0, cnt = 0;
  for (auto e: es) {
    int d = e.first, u = e.second.first, v = e.second.second;
    if (uf.merge(u, v)) {
      ans += d;
      ++cnt;
    }
    if (cnt == max_grp - 1) break;
  }
  if (cnt != max_grp - 1) cout << -1;
  else cout << ans;
}
