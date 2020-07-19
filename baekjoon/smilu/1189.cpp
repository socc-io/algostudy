#include <bits/stdc++.h>
using namespace std;

const int dd[4][2] = {{-1,0},{1,0},{0,1},{0,-1}};

int h, w, k;
char tile[5][6];

struct state {
  int _cnt;
  int _visit;
  int _cur;
  state(int cnt, int visit, int cur): _cnt(cnt), _visit(visit), _cur(cur) {}
  int x() const { return _cur / w; }
  int y() const { return _cur % w; }
  bool visit(int x, int y) const {
    const int id = x*w + y;
    return (_visit & (1 << id)) > 0;
  }
  state next(int nx, int ny) {
    const int nid = nx * w + ny;
    return state(
      _cnt + 1,
      _visit | (1 << nid),
      nid
    );
  }
};

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> h >> w >> k;
  for (int i = 0; i < h; i++) cin >> tile[i];

  state init_state(1, 1 << ((h-1)*w), (h-1)*w);
  queue<state> q;
  int ans = 0;
  const int dst = w-1;
  q.push(init_state);
  while (!q.empty()) {
    state u = q.front(); q.pop();
    if (u._cnt == k) {
      ans += u._cur == dst;
      continue;
    }
    const int ux = u.x(), uy = u.y();
    for (int di = 0; di < 4; di++) {
      const int vx = ux + dd[di][0], vy = uy + dd[di][1];
      if (vx < 0 || vx >= h || vy < 0 || vy >= w) continue;
      if (tile[vx][vy] != '.') continue;
      if (u.visit(vx, vy)) continue;
      state v = u.next(vx, vy);
      q.push(v);
    }
  }
  cout << ans << '\n';
}
