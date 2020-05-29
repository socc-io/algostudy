#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pi;

const int dd[4][2] = {
  {-1,0},{0,1},{0,-1},{1,0}
};

struct Environment {
  int r, c;
  int mineral[111][111];
  int grp[111][111];
  int min_x[10000];
  vector<pi> memb[10000];
  void input() {
    char buf[101];
    cin >> r >> c;
    for (int i = 0; i < r; i++) {
      cin >> buf;
      for (int j = 0; j < c; j++) {
        mineral[r-i][j+1] = (buf[j] != '.');
      }
    }
  }
  void print() {
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        cout << (mineral[r-i][j+1] ? 'x' : '.');
      } cout << '\n';
    } cout << '\n';
  }
  void group_dfs(int x, int y, int g) {
    grp[x][y] = g;
    memb[g].emplace_back(x, y);
    for (int di = 0; di < 4; di++) {
      int nx = x + dd[di][0], ny = y + dd[di][1];
      if (nx < 1 || nx > r || ny < 1 || ny > c) continue;
      if (!mineral[nx][ny]) continue;
      if (grp[nx][ny]) continue;
      group_dfs(nx, ny, g);
    }
  }
  int group() {
    memset(grp, 0x00, sizeof(grp));
    int g = 0;
    for (int i = 1; i <= r; i++) {
      for (int j = 1; j <= c; j++) {
        if (!mineral[i][j]) continue;
        if (grp[i][j]) continue;
        min_x[++g] = i;
        memb[g].clear();
        group_dfs(i, j, g);
      }
    }
    return g;
  }
  bool fall(int g) {
    bool ret = true;
    for (auto &pos: memb[g]) {
      mineral[pos.first][pos.second]--;
    }
    for (auto &pos: memb[g]) {
      pos.first--;
      mineral[pos.first][pos.second]++;
      if (mineral[pos.first][pos.second] > 1) ret = false;
      if (pos.first == 0) ret = false;
    }
    return ret;
  }
  void back(int g) {
    for (auto &pos: memb[g]) {
      mineral[pos.first][pos.second]--;
      pos.first++;
      mineral[pos.first][pos.second]++;
    }
  }
  void run_gravity() {
    int n = group();
    int g = 1;
    while (g <= n && min_x[g] == 1) g++;
    if (g > n) return;
    while (fall(g));
    back(g);
  }
  void remove(int x, int y) {
    mineral[x][y]--; 
    run_gravity();
  }
  void remove_left(int x) {
    int y = 1;
    while (y <= c && !mineral[x][y]) ++y;
    if (y <= c) remove(x, y);
  }
  void remove_right(int x) {
    int y = c;
    while (y >= 1 && !mineral[x][y]) --y;
    if (y >= 1) remove(x, y);
  }
} env;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  env.input();
  int n; cin >> n;
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    (i&1) ? env.remove_right(x) : env.remove_left(x);
  }
  env.print();
}
