#include <bits/stdc++.h>
using namespace std;

const int dd[4][2] = {
  {-1,0},{1,0},{0,1},{0,-1},
};

class UnionFind {
  vector<int> par;
public:
  UnionFind(int n) {
    par.resize(n);
    iota(par.begin(), par.end(), 0);
  }
  int root(int v) {
    return par[v] == v ? v : (par[v] = root(par[v]));
  }
  bool merge(int a, int b) {
    a = root(a);
    b = root(b);
    if (a == b) return false;
    par[b] = a;
    return true;
  }
  bool like(int a, int b) { return root(a) == root(b); }
};

int n;

int count_star(const vector<string> &tile) {
  int ret = 0;
  for (const string &line: tile) {
    for (const char ch: line) {
      ret += ch == '*';
    }
  }
  return ret;
}

struct point {
  int x, y;
  bool operator==(const point &p) const {
    return x == p.x && y == p.y;
  }
  bool is_adjacent(const point &p) const {
    const int dx = abs(x - p.x);
    const int dy = abs(y - p.y);
    return (dx == 1 && dy == 0) || (dx == 0 && dy == 1);
  }
};

bool is_unique_points(const vector<point> &ps) {
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      if (ps[i] == ps[j]) return false;
    }
  }
  return true;
}

struct state {
  int v;
  state(const vector<point> &points) {
    v = 0;
    for (const point &p: points) {
      v |= 1 << (p.x*5 + p.y);
    }
  }
  state(const vector<string> &tile) {
    v = 0;
    int idx = 0;
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        if (tile[i][j] == '*') v |= (1 << idx);
        ++idx;
      }
    }
  }
  bool is_final() const {
    const vector<point> points = get_points();
    UnionFind uf(n);
    for (int i = 0; i < n; i++) {
      for (int j = i+1; j < n; j++) {
        if (points[i].is_adjacent(points[j])) {
          uf.merge(i, j);
        }
      }
    }
    for (int i = 0; i < n-1; i++) {
      if (!uf.like(i, i+1)) return false;
    }
    return true;
  }
  vector<point> get_points() const {
    vector<point> ret;
    int det = 1;
    for (int i = 0; i < 25; i++) {
      if (v & det) {
        ret.push_back({i/5, i%5});
      }
      det <<= 1;
    }
    return ret;
  }
  vector<state> get_adjacents() const {
    vector<state> ret;
    vector<point> points = get_points();
    for (int pi = 0; pi < n; pi++) {
      const int x = points[pi].x, y = points[pi].y;
      for (int di = 0; di < 4; di++) {
        const int nx = x + dd[di][0];
        const int ny = y + dd[di][1];
        if (nx < 0 || ny < 0 || nx >= 5 || ny >= 5) continue;
        points[pi].x = nx;
        points[pi].y = ny;
        if (!is_unique_points(points)) continue;
        ret.push_back(state(points));
      }
      points[pi].x = x;
      points[pi].y = y;
    }
    return ret;
  }
  void print() const {
    int idx = 0;
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        cout << ((v & (1 << idx)) ? '*' : '.');
        ++idx;
      } cout << '\n';
    }
  }
};

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  vector<string> tile(5);
  for (string &s: tile) cin >> s;
  n = count_star(tile);
  state s(tile);
  queue<state> q;
  map<int, int> dist;
  q.push(s);
  dist[s.v] = 0;
  while (!q.empty()) {
    state u = q.front(); q.pop();
    if (u.is_final()) {
      cout << dist[u.v] << '\n';
      // u.print();
      return 0;
    }
    int vd = dist[u.v] + 1;
    for (const state v: u.get_adjacents()) {
      auto it = dist.find(v.v);
      if (it != dist.end()) continue;
      dist.insert(make_pair(v.v, vd));
      q.push(v);
    }
  }
}
