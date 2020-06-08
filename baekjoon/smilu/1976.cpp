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
  int n, m;
  cin >> n >> m;
  UnionFind uf(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int cc; cin >> cc;
      if (cc == 0) continue;
      uf.merge(i, j);
    }
  }
  int p; cin >> p;
  for (int i = 1; i < m; i++) {
    int q; cin >> q;
    if (!uf.like(p-1, q-1)) {
      cout << "NO\n";
      return 0;
    }
    p = q;
  }
  cout << "YES\n";
}
