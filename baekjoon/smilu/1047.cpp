#include <bits/stdc++.h>
using namespace std;

struct Tree {
  int x, y, w;
  bool operator<(const Tree &t) const { return w > t.w; }
};

inline bool inside(int x, int y, int xb, int xe, int yb, int ye) {
  return xb<=x && x<=xe && yb<=y && y<=ye;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n; cin >> n;
  vector<Tree> ts(n);
  vector<int> x(n), y(n);
  for (int i = 0; i < n; i++) {
    cin >> ts[i].x >> ts[i].y >> ts[i].w;
    x[i] = ts[i].x;
    y[i] = ts[i].y;
  }
  sort(ts.begin(), ts.end());
  sort(x.begin(), x.end());
  sort(y.begin(), y.end());
  
  int ans = n;
  for (int xb = 0; xb < n; xb++) {
    const int min_x = x[xb];
    for (int xe = xb; xe < n; xe++) {
      const int max_x = x[xe];
      for (int yb = 0; yb < n; yb++) {
        const int min_y = y[yb];
        for (int ye = yb; ye < n; ye++) {
          const int max_y = y[ye];
          int rd = (max_x-min_x+max_y-min_y)<<1;
          int cnt = 0;
          vector<int> ics;
          ics.push_back(0);
          for (const Tree &t: ts) {
            if (inside(t.x, t.y, min_x, max_x, min_y, max_y)) {
              ics.push_back(ics.back() + t.w);
            } else {
              rd -= t.w;
              ++cnt;
            }
          }
          if (rd > 0) cnt += distance(ics.begin(), lower_bound(ics.begin(), ics.end(), rd));
          ans = min(ans, cnt);
        }
      }
    }
  }
  cout << ans;
}
