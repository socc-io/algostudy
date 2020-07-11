#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pi;

const int dd[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
const int dc[4][2] = {{0,0},{0,0},{0,1},{1,0}};

int n, m;
int init_l, init_r;
int start_x, start_y;
char tile[1010][1010];

struct state {
  int x, y;
  int l, r;
  state(int x=0, int y=0, int l=0, int r=0):
    x(x),y(y),l(l),r(r) {}
  void print() {
    cout << '(' << x << ", " << y << ", " << l << ", " << r << ')';
  }
};

struct history {
  set<pi> records;
  int min_l, min_r;
  history() {
    min_l = -1;
    min_r = -1;
  }
  void add(int l, int r) {
    if (min_l == -1) {
      min_l = l;
      min_r = r;
    } else {
      min_l = min(min_l, l);
      min_r = min(min_r, r);
    }
    records.insert({l, r});
  }
  bool check(int l, int r) const {
    if (min_l == -1) return true;
    if (l <= min_l && r <= min_r) return false;
    if (records.find({l, r}) != records.end()) return false;
    return true;
  }
  bool visit() const { return min_l != -1; }
} hs[1010][1010];

state init_state;

void find_start() {
  bool flag = false;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (tile[i][j] != '2') continue;
      start_x = i;
      start_y = j;
      tile[i][j] = '0';
      flag = true;
      break;
    }
    if (flag) break;
  }
  init_state = state(start_x, start_y, init_l, init_r);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n >> m >> init_l >> init_r;
  for (int i = 0; i < n; i++) cin >> tile[i];
  find_start();
  queue<state> q;
  hs[start_x][start_y].add(init_l, init_r);
  q.push(init_state);
  // cout << "init: "; init_state.print(); cout << '\n';
  while (!q.empty()) {
    state u = q.front(); q.pop();
    for (int di = 0; di < 4; di++) {
      const int nx = u.x + dd[di][0], ny = u.y + dd[di][1];
      if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
      if (tile[nx][ny] == '1') continue;
      const int nl = u.l - dc[di][0], nr = u.r - dc[di][1];
      if (nl < 0 || nr < 0) continue;
      auto &h = hs[nx][ny];
      if (!h.check(nl, nr)) continue;
      h.add(nl, nr);
      q.push(state(nx, ny, nl, nr));
      // cout << "push: "; q.back().print(); cout << '\n';
    }
  }
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (tile[i][j] == '1') continue;
      cnt += hs[i][j].visit();
    }
  }

  // for (int i = 0; i < n; i++) {
  //   for (int j = 0; j < m; j++) {
  //     if (tile[i][j] == '1') cout << 'x';
  //     else cout << (hs[i][j].visit() ? 'o' : '.');
  //   } cout << '\n';
  // }

  cout << cnt;
}
