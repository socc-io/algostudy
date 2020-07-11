#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pi;

int n, m;
int init_l, init_r;
int start_x, start_y;
char tile[1010][1010];
int top[1010][1010];
vector<pi> adj[1010][1010];

struct state {
  int x, y, l, r;
  state(int x, int y, int l, int r):
    x(x),y(y),l(l),r(r) {}
};

struct history {
  set<pi> records;
  int ml, mr;
  history() {
    ml = mr = 0x3f3f3f3f;
  }
  bool check(int l, int r) const {
    if (records.empty()) return true;
    if (l <= ml && r <= mr) return false;
    if (records.find({l, r}) != records.end()) return false;
    return true;
  }
  void add(int l, int r) {
    records.insert({l, r});
    ml = min(ml, l);
    mr = min(mr, r);
  }
  bool visit() const { return !records.empty(); }
} hs[1010][1010];

void init_start() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (tile[i][j] != '2') continue;
      start_x = i;
      start_y = j;
      tile[i][j] = '0';
      return;
    }
  }
}

void init_top() {
  memset(top, 0xff, sizeof(top));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      top[i][j] = i;
    }
  }
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (tile[i][j] == '1') continue;
      if (tile[i-1][j] == '1') continue;
      top[i][j] = top[i-1][j];
    }
  }
}

void init_adj(const int x, const int y) {
  const int ry = y + 1;
  const int ly = y - 1;
  vector<pi> &as = adj[x][y];
  int cx = x;
  while (cx < n && tile[cx][y] == '0') {
    if (tile[cx][ry] == '0') {
      const int rx = top[cx][ry];
      if (as.empty() || as.back() != make_pair(rx, ry)) {
        as.emplace_back(rx, ry);
      }
    }
    ++cx;
  }
  cx = x;
  while (cx < n && tile[cx][y] == '0') {
    if (tile[cx][ly] == '0') {
      const int lx = top[cx][ly];
      if (as.empty() || as.back() != make_pair(lx, ly)) {
        as.emplace_back(lx, ly);
      }
    }
    ++cx;
  }
}

void init_adjs() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (top[i][j] != i) continue;
      init_adj(i, j);
    }
  }
}

inline pi origin(pi x) { return make_pair(top[x.first][x.second], x.second); }

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n >> m >> init_l >> init_r;
  for (int i = 0; i < n; i++) cin >> tile[i];
  init_start();
  init_top();
  init_adjs();

  start_x = top[start_x][start_y];
  state init_state(start_x, start_y, init_l, init_r);
  queue<state> q;
  q.push(init_state);
  hs[start_x][start_y].add(init_l, init_r);
  while (!q.empty()) {
    auto u = q.front(); q.pop();
    for (const auto &nxt: adj[u.x][u.y]) {
      int nl = u.l - (nxt.second < u.y ? 1 : 0);
      int nr = u.r - (nxt.second > u.y ? 1 : 0);
      if (nl < 0 || nr < 0) continue;
      auto &h = hs[nxt.first][nxt.second];
      if (!h.check(nl, nr)) continue;
      h.add(nl, nr);
      q.push(state(nxt.first, nxt.second, nl, nr));
    }
  }
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (tile[i][j] == '1') continue;
      cnt += hs[top[i][j]][j].visit();
    }
  }

  // for (int i = 0; i < n; i++) {
  //   for (int j = 0; j < m; j++) {
  //     if (tile[i][j] == '1') cout << '1';
  //     else cout << (hs[top[i][j]][j].visit() ? 'o' : 'x');
  //   } cout << '\n';
  // }

  cout << cnt;
}
