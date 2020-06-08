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

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n, m; cin >> n >> m;
  UnionFind uf(n+1);
  while (m--) {
    int cmd, a, b;
    cin >> cmd >> a >> b;
    if (cmd == 0) {
      uf.merge(a, b);
    } else if (cmd == 1) {
      cout << (uf.like(a, b) ? "YES" : "NO") << '\n';
    }
  }
}
