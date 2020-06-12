#include <bits/stdc++.h>
using namespace std;

class UnionFind {
  vector<int> par;
  vector<int> wei;
public:
  UnionFind(int n) {
    par.resize(n);
    wei.resize(n, 0);
    iota(par.begin(), par.end(), 0);
  }
  int root(int v) {
    return par[v] == v ? v : (par[v] = root(par[v]));
  }
  void add_weight(int v, int alpha) { wei[v] += alpha; }
  int weight(int v) { return wei[root(v)]; }
  bool merge(int a, int b) {
    a = root(a);
    b = root(b);
    if (a == b) return false;
    par[b] = a;
    wei[a] += wei[b];
    return true;
  }
  bool like(int a, int b) { return root(a) == root(b); }
};

class Topological {
public:
  const int n;
  vector<vector<int>> adj;
  void add_edge(int u, int v) { adj[u].push_back(v); }
  vector<int> get_nin() {
    vector<int> nin(n);
    for (int u = 0; u < n; u++) {
      for (int v: adj[u]) {
        nin[v]++;
      }
    }
    return nin;
  }
  vector<int> leafs(const vector<int> &nin) {
    vector<int> ret;
    for (int i = 0; i < n; i++) {
      if (nin[i] == 0) ret.push_back(i);
    }
    return ret;
  }
  vector<int> leafs() {
    return leafs(get_nin());
  }
  vector<int> get_ord() {
    vector<int> nin = get_nin();
    vector<int> ord(n);
    int piv = 1;
    queue<int> q;
    for (int u: leafs(nin)) q.push(u);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      ord[u] = piv++;
      for (int v: adj[u]) {
        nin[v]--;
        if (nin[v] == 0) q.push(v);
      }
    }
    return ord;
  }
  Topological(int n): n(n), adj(n) {}
};

class SCC: public vector<vector<int>> {
  vector<int> dfsn;
  vector<int> sn;
  vector<bool> finished;
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
  vector<int> execute() {
    piv = 0;
    sn.resize(n, 0);
    dfsn.resize(n, 0);
    finished.resize(n, false);
    while (!s.empty()) s.pop();
    for (int i = 0; i < n; i++) {
      if (dfsn[i] == 0) dfs(i);
    }
    return sn;
  }
  SCC(int n): n(n), adj(n) {}
};

vector<int> solve() {
  int n, m; cin >> n >> m;

  SCC scc(n);
  for (int i = 0; i < m; i++) {
    int a, b; cin >> a >> b;
    scc.add_edge(a, b);
  }
  auto sn = scc.execute();

  Topological tg(scc.size());
  for (int i = 0; i < n; i++) {
    for (int j: scc.adj[i]) {
      int u = sn[i], v = sn[j];
      if (u != v) tg.add_edge(u, v);
    }
  }
  auto leafs = tg.leafs();
  if (leafs.size() != 1) return vector<int>();
  return scc[leafs[0]];
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t;
  while (t--) {
    auto ans = solve();
    if (ans.empty()) cout << "Confused\n";
    else for (int v: ans) cout << v << '\n';
    cout << '\n';
  }
}
