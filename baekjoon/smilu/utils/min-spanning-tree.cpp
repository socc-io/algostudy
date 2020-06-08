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
