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
      vs[n] = min(vs[n], val);
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
  int mx, Mx, my, My, w;
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

vector<int> solve() {
  int sz_grid, num_ship, num_laser;
  cin >> sz_grid >> num_ship >> num_laser;
  
  vector<Ship> ships(num_ship);
  vector<Laser> lasers(num_laser);
  for (auto &ship: ships) ship.input();
  for (auto &laser: lasers) laser.input();
  
  Zipper x_zipper, y_zipper;
  for (auto &ship: ships) {
    x_zipper.add(ship.mx);
    x_zipper.add(ship.Mx);
    y_zipper.add(ship.my);
    y_zipper.add(ship.My);
  }
  for (auto &laser: lasers) {
    if (laser.x != -1) x_zipper.add(laser.x);
    if (laser.y != -1) y_zipper.add(laser.y);
  }
  x_zipper.organize();
  y_zipper.organize();
  for (auto &ship: ships) {
    ship.mx = x_zipper.get(ship.mx);
    ship.Mx = x_zipper.get(ship.Mx);
    ship.my = y_zipper.get(ship.my);
    ship.My = y_zipper.get(ship.My);
  }
  for (auto &laser: lasers) {
    if (laser.x != -1) laser.x = x_zipper.get(laser.x);
    if (laser.y != -1) laser.y = y_zipper.get(laser.y);
  }

  MinSegTree x_seg, y_seg;
  x_seg.set_se(0, (int)x_zipper.size() - 1);
  y_seg.set_se(0, (int)y_zipper.size() - 1);

  for (int i = 0; i < num_laser; i++) {
    const auto &laser = lasers[i];
    if (laser.x != -1) x_seg.update(laser.x, i);
    if (laser.y != -1) y_seg.update(laser.y, i);
  }
  
  vector<int> ans(num_laser);
  for (const auto &ship: ships) {
    int x_idx = x_seg.query(ship.mx, ship.Mx);
    int y_idx = y_seg.query(ship.my, ship.My);
    int idx = min(x_idx, y_idx);
    if (idx == L_INF) continue;
    ans[idx] = max(ans[idx], ship.w);
  }

  return ans;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t;
  while (t--) for (int v: solve()) {
    cout << v << '\n';
  }
}
