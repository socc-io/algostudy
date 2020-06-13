#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;

class SCC: public vector<vector<int>> {
  vector<int> dfsn;
  vector<bool> finished;
  vector<int> sn;
  stack<int> s;
  int piv;
public:
  int n;
  vector<vector<int>> adj;
  void add_edge(int u, int v) { adj[u].push_back(v); }
  int dfs(int u) {
    dfsn[u] = ++piv;
    s.push(u);

    int res = dfsn[u];
    for (int v: adj[u]) {
      if (dfsn[v] == 0) res = min(res, dfs(v));
      else if (!finished[v]) res = min(res, dfsn[v]);
    }

    if (res == dfsn[u]) {
      vector<int> vs;
      while (1) {
        int t = s.top(); s.pop();
        vs.push_back(t);
        finished[t] = true;
        sn[t] = size();
        if (t == u) break;
      }
      sort(vs.begin(), vs.end());
      push_back(vs);
    }

    return res;
  }
  void execute() {
    piv = 0;
    sn.resize(n, 0);
    dfsn.resize(n, 0);
    finished.resize(n, false);
    while (!s.empty()) s.pop();
    for (int i = 0; i < n; i++) {
      if (dfsn[i] == 0) dfs(i);
    }
  }
  int get(int x) const { return sn[x]; }
  SCC(int n): n(n), adj(n) {}
};

class TwoSAT {
  SCC scc;
  int _id(int x) {
    if (x < 0) return n2+x;
    return x-1;
  }
  int _not(int x) {
    return n2-1-x;
  }
public:
  const int n, n2;
  TwoSAT(int n): scc(n*2), n(n), n2(n*2) {}
  void add_edge(int u, int v) {
    u = _id(u); v = _id(v);
    int nu = _not(u), nv = _not(v);
    scc.add_edge(u, v);
    scc.add_edge(nv, nu);
  }
  vector<int> execute() {
    vector<int> pred;

    scc.execute();
    for (int i = 0; i < n; i++) {
      int j = _not(i);
      if (scc.get(i) == scc.get(j)) return pred;
    }

    vector<pi> ps(n2);
    for (int i = 0; i < n2; i++)
      ps[i] = {scc.get(i), i};
    sort(ps.begin(), ps.end());

    pred.resize(n);
    for (int i = n2-1; i >= 0; i--) {
      int u = ps[i].second;
      int v = (u >= n ? _not(u) : u);
      if (pred[v] == 0) pred[v] = (u>=n) ? 1 : -1;
    }

    return pred;
  }
};

vector<int> solve() {
  int n, m; cin >> n >> m;
  TwoSAT sat(n);
  while (m--) {
    int a, b; cin >> a >> b;
    sat.add_edge(-a, b);
  }
  auto pred = sat.execute();
  return pred;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  auto r = solve();
  if (r.empty()) cout << "0\n";
  else {
    cout << "1\n";
    for (int v: r) cout << (v > 0) << ' '; cout << '\n';
  }
}
