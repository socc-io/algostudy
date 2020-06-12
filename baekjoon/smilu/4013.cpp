#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;

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

int solve() {
  int n, m; cin >> n >> m;
  vector<int> wei(n, 0);
  SCC scc(n);
  for (int i = 0; i < m; i++) {
    int a, b; cin >> a >> b;
    scc.add_edge(a-1, b-1);
  }
  for (int i = 0; i < n; i++) cin >> wei[i];
  
  auto sn = scc.execute();

  vector<int> s_wei(scc.size());
  for (int i = 0; i < n; i++) {
    s_wei[sn[i]] += wei[i];
  }
  
  vector<vector<int>> adj(scc.size());
  for (int i = 0; i < n; i++) {
    for (int j: scc.adj[i]) {
      int a = sn[i], b = sn[j];
      if (a != b) adj[a].push_back(b);
    }
  }

  queue<int> q;
  vector<bool> in_q(scc.size());
  vector<int> dist(scc.size());
  int s; cin >> s; s = sn[s-1];
  q.push(s);
  in_q[s] = true;
  dist[s] = s_wei[s];
  while (!q.empty()) {
    auto u = q.front(); q.pop();
    for (int v: adj[u]) {
      int vd = dist[u] + s_wei[v];
      if (vd > dist[v]) {
        dist[v] = vd;
        if (!in_q[v]) q.push(v);
      }
    }
  }

  int p, ret; cin >> p;
  for (int i = 0; i < p; i++) {
    int pi; cin >> pi;
    ret = max(ret, dist[sn[pi-1]]);
  }
  return ret;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << solve() << '\n';
}
