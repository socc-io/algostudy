#include <bits/stdc++.h>
using namespace std;

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

class MinSpanningTree {
  struct Edge {
    double w;
    int a, b;
    bool operator<(const Edge &e) const {
      if (w != e.w) return w < e.w;
      if (a != e.a) return a < e.a;
      return b < e.b;
    }
    Edge(double w, int a, int b): w(w),a(a),b(b) {}
  };
  vector<Edge> edges;
public:
  void add_edge(int a, int b, double w) {
    edges.push_back(Edge(w, a, b));
  }
  vector<Edge> execute(int n) {
    vector<Edge> ret;
    sort(edges.begin(), edges.end());
    UnionFind uf(n);
    for (auto edge: edges) {
      int a = edge.a, b = edge.b;
      if (uf.merge(a, b)) {
        ret.push_back(edge);
      }
    }
    return ret;
  }
};

struct point {
  double x, y;
  point operator-(const point &p) const {
    return point(x-p.x, y-p.y);
  }
  double distance(const point &p) const {
    return sqrt(((*this)-p).hypot());
  }
  double hypot() {
    return x*x+y*y;
  }
  point(double x, double y): x(x),y(y) {}
  point() {}
};

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n, m; cin >> n >> m;
  vector<point> points(n);
  for (auto &p: points) cin >> p.x >> p.y;
  MinSpanningTree mt;
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      double w = points[i].distance(points[j]);
      mt.add_edge(i, j, w);
    }
  }
  for (int i = 0; i < m; i++) {
    int a, b; cin >> a >> b;
    mt.add_edge(a-1, b-1, 0);
  }
  auto edges = mt.execute(n+1);
  double w_sum = 0;
  for (const auto &e: edges) w_sum += e.w;
  cout << fixed;
  cout.precision(2);
  cout << w_sum << '\n';
}
