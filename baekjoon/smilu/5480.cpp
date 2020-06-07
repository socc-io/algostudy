#include <bits/stdc++.h>
using namespace std;

const int SEG_SZ = 1<<19;
const int L_INF = 0x7fffffff;

class MinSegTree {
  vector<int> vs;
  int _s, _e;
public:
  void set_se(int s, int e) {
    _s = s;
    _e = e;
  }
  void update(int n, int s, int e, int x, int val) {
    if (s == e) {
      vs[n] = val;
      return;
    }
    int m = (s+e)>>1, l = n<<1, r = l|1;
    if (x <= m) update(l,s,m,x,val);
    else update(r,m+1,e,x,val);
    vs[n] = min(vs[l], vs[r]);
  }
  void update(int x, int val) {
    update(1, _s, _e, x, val);
  }
  int query(int n, int s, int e, int f, int t) {
    if (t < s || e < f) return L_INF;
    if (f <= s && e <= t) return vs[n];
    int m = (s+e)>>1, l = n<<1, r = l|1;
    auto L = query(l,s,m,f,t);
    auto R = query(r,m+1,e,f,t);
    return min(L, R);
  }
  int query(int f, int t) {
    return query(1, _s, _e, f, t);
  }
  MinSegTree(int cap = SEG_SZ, int iv = L_INF) {
    vs.resize(cap, iv);
  }
};

class Zipper: public vector<int> {
public:
  void add(int v) { push_back(v); }
  void organize() {
    sort(begin(), end());
    erase(unique(begin(), end()), end());
  }
  int get(int v) {
    auto lo = lower_bound(begin(), end(), v);
    return distance(begin(), lo);
  }
};

struct Ship {
  int mx, Mx;
  int my, My;
  int w;
  void input() {
    int a0, a1, a2, a3;
    cin >> a0 >> a1 >> a2 >> a3 >> w;
    mx = min(a0, a2);
    Mx = max(a0, a2);
    my = min(a1, a3);
    My = max(a1, a3);
  }
};

struct Laser {
  int x, y;
  void input() {
    int a, b; cin >> a >> b;
    if (b) {
      x = a;
      y = -1;
    } else {
      x = -1;
      y = a;
    }
  }
};

void solve() {
  int sz_grid, num_ship, num_laser;
  cin >> sz_grid >> num_ship >> num_laser;

  Zipper x_zipper, y_zipper;

  vector<Ship> ships(num_ship);
  for (int i = 0; i < num_ship; i++) {
    ships[i].input();
    x_zipper.add(ships[i].mx);
    x_zipper.add(ships[i].Mx);
    y_zipper.add(ships[i].my);
    y_zipper.add(ships[i].My);
  }

  vector<Laser> lasers(num_laser);
  for (int i = 0; i < num_laser; i++) {
    lasers[i].input();
    if (lasers[i].x != -1) x_zipper.add(lasers[i].x);
    if (lasers[i].y != -1) y_zipper.add(lasers[i].y);
  }

  x_zipper.organize();
  y_zipper.organize();

  for (int i = 0; i < num_ship; i++) {
    ships[i].mx = x_zipper.get(ships[i].mx);
    ships[i].Mx = x_zipper.get(ships[i].Mx);
    ships[i].my = y_zipper.get(ships[i].my);
    ships[i].My = y_zipper.get(ships[i].My);
  }
  for (int i = 0; i < num_laser; i++) {
    if (lasers[i].x != -1) lasers[i].x = x_zipper.get(lasers[i].x);
    if (lasers[i].y != -1) lasers[i].y = y_zipper.get(lasers[i].y);
  }

  MinSegTree x_seg, y_seg;
  x_seg.set_se(0, (int)x_zipper.size() - 1);
  y_seg.set_se(0, (int)y_zipper.size() - 1);

  for (int i = num_laser - 1; i >= 0; i--) {
    const auto &laser = lasers[i];
    if (laser.x != -1) x_seg.update(laser.x, i);
    if (laser.y != -1) y_seg.update(laser.y, i);
  }
  
  vector<int> ans(num_laser);
  for (int i = 0; i < num_ship; i++) {
    const auto &ship = ships[i];
    int x_idx = x_seg.query(ship.mx, ship.Mx);
    int y_idx = y_seg.query(ship.my, ship.My);
    int idx = min(x_idx, y_idx);
    if (idx == L_INF) continue;
    ans[idx] = max(ans[idx], ship.w);
  }

  for (int v: ans) cout << v << '\n';
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t;
  while (t--) solve();
}
