#include <bits/stdc++.h>
using namespace std;

const int inf = 0x3f3f3f3f;

int w, h;
char tile[1500][1501];

bool lh[1500][1500];
bool rh[1500][1500];

int a_lh[1501][1501];
int a_rh[1501][1501];
int a_bk[1501][1501];

void init_acc_maps() {
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      a_lh[i][j] = a_lh[i][j-1] + a_lh[i-1][j] - a_lh[i-1][j-1] + lh[i-1][j-1];
    }
  }
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      a_rh[i][j] = a_rh[i][j-1] + a_rh[i-1][j] - a_rh[i-1][j-1] + rh[i-1][j-1];
    }
  }
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      a_bk[i][j] = a_bk[i][j-1] + a_bk[i-1][j] - a_bk[i-1][j-1] + (tile[i-1][j-1] == '#');
    }
  }
}

void c_clockwise(int &dx, int &dy) {
  int tmp = dx;
  dx = -dy;
  dy = tmp;
}

void clockwise(int &dx, int &dy) {
  int tmp = dx;
  dx = dy;
  dy = -tmp;
}

bool dot(int x, int y) {
  if (x < 0 || x >= h || y < 0 || y >= w) return false;
  return tile[x][y] == '.';
}

void set_lh() {
  int cx = 0, cy = 0, dx = 0, dy = 1;
  while (1) {
    lh[cx][cy] = true;
    if (cx == h-1 && cy == w-1) break;
    c_clockwise(dx, dy);
    if (!dot(cx+dx, cy+dy)) {
      clockwise(dx, dy);
      if (!dot(cx+dx, cy+dy)) {
        clockwise(dx, dy);
        if (!dot(cx+dx, cy+dy)) clockwise(dx, dy);
      }
    }
    cx += dx;
    cy += dy;
  }
}

void set_rh() {
  int cx = 0, cy = 0, dx = 1, dy = 0;
  while (1) {
    rh[cx][cy] = true;
    if (cx == h-1 && cy == w-1) break;
    clockwise(dx, dy);
    if (!dot(cx+dx, cy+dy)) {
      c_clockwise(dx, dy);
      if (!dot(cx+dx, cy+dy)) {
        c_clockwise(dx, dy);
        if (!dot(cx+dx, cy+dy)) c_clockwise(dx, dy);
      }
    }
    cx += dx;
    cy += dy;
  }
}

bool check_lh(int x, int y, int l) {
  int mx = x + l, my = y + l;
  return a_lh[mx][my] - a_lh[mx][y] - a_lh[x][my] + a_lh[x][y] > 0;
}

bool check_rh(int x, int y, int l) {
  int mx = x + l, my = y + l;
  return a_rh[mx][my] - a_rh[mx][y] - a_rh[x][my] + a_rh[x][y] > 0;
}

bool check_include(int x, int y, int l, int tx, int ty) {
  return x <= tx && tx < x + l && y <= ty && ty < y + l;
}

bool check_bk(int x, int y, int l) {
  int mx = x + l, my = y + l;
  if (check_include(x, y, l, h-1, w-1)) return false;
  return a_bk[mx][my] - a_bk[mx][y] - a_bk[x][my] + a_bk[x][y] == 0;
}

bool check_rg(int x, int y, int l) {
  int mx = x + l, my = y + l;
  return mx <= h && my <= w;
}

bool check_box(int x, int y, int l) {
  return check_lh(x, y, l) && check_rh(x, y, l);
}

bool check_l(int x, int y, int l) {
  return check_rg(x, y, l) && check_bk(x, y, l);
}

int find_max_l(int x, int y) {
  int lo = 1, up = min(w, h);
  while (lo + 1 < up) {
    int md = (lo + up) >> 1;
    if (check_l(x, y, md)) {
      lo = md;
    } else {
      up = md;
    }
  }
  if (check_l(x, y, up)) return up;
  return lo;
}

int find_min_l(int x, int y) {
  int lo = 1, up = find_max_l(x, y);
  while (lo + 1 < up) {
    int md = (lo + up) >> 1;
    if (check_box(x, y, md)) {
      up = md;
    } else {
      lo = md;
    }
  }
  if (check_box(x, y, lo)) return lo;
  if (check_box(x, y, up)) return up;
  return inf;
}

pair<int, pair<int, int>> solve() {
  cin >> w >> h;
  for (int i = 0; i < h; i++) cin >> tile[i];
  set_lh();
  set_rh();
  init_acc_maps();

  int ans = inf;
  int ans_x = -1;
  int ans_y = -1;
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      if (tile[i][j] != '.') continue;
      if (i == 0  && j == 0) continue;
      if (i == h-1 && j == w-1) continue;
      int ml = find_min_l(i, j);
      if (ans > ml) {
        ans = ml;
        ans_x = i;
        ans_y = j;
      }
    }
  }

  if (ans == inf) throw -1;

  // for (int i = 0; i < h; i++) {
  //   for (int j = 0; j < w; j++) {
  //     if (tile[i][j] == '#') cout << '#';
  //     else {
  //       if (lh[i][j] && !rh[i][j]) cout << '*';
  //       else if (!lh[i][j] && rh[i][j]) cout << '^';
  //       else if (lh[i][j] && rh[i][j]) cout << '&';
  //       else cout << '.';
  //     }
  //   }
  //   cout << '\n';
  // }

  return make_pair(ans, make_pair(ans_y+1, ans_x+1));
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  try {
    auto res = solve();
    cout << res.first << ' ' << res.second.first << ' ' << res.second.second << '\n';
  } catch (int err) {
    cout << "Impossible\n";
  }
}
