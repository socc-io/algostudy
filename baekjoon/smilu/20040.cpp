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

int n, m;

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n >> m;
  UnionFind uf(n);
  int ans = 0;
  for (int i = 0; i < m; i++) {
    int a, b; cin >> a >> b;
    if (!uf.merge(a, b)) {
      ans = i+1;
      break;
    }
  }
  cout << ans;
}
