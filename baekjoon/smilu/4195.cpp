#include <bits/stdc++.h>
using namespace std;

class Dictionary {
  map<string, int> ids;
  vector<string> lst;
public:
  int id(const string &s) {
    auto f = ids.find(s);
    if (f == ids.end()) {
      ids[s] = lst.size();
      lst.push_back(s);
      return lst.size() - 1;
    }
    return f->second;
  }
  string get(int id) { return lst[id]; }
};

class UnionFind {
  vector<int> par;
  vector<int> sz;
public:
  UnionFind(int n) {
    par.resize(n);
    sz.resize(n);
    iota(par.begin(), par.end(), 0);
    for (int i = 0; i < n; i++) sz[i] = 1;
  }
  int root(int v) {
    return par[v] == v ? v : (par[v] = root(par[v]));
  }
  int size(int v) { return sz[root(v)]; }
  bool merge(int a, int b) {
    a = root(a);
    b = root(b);
    if (a == b) return false;
    par[b] = a;
    sz[a] += sz[b];
    return true;
  }
  bool like(int a, int b) { return root(a) == root(b); }
};

void solve() {
  int f; cin >> f;
  UnionFind uf(200000);
  Dictionary dict;
  while (f--) {
    string a, b; cin >> a >> b;
    int ai = dict.id(a);
    int bi = dict.id(b);
    uf.merge(ai, bi);
    cout << uf.size(ai) << '\n';
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t;
  while (t--) solve();
}
