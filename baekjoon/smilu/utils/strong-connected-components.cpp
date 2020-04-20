#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

struct SCC {
  int n;
  vector<vector<int>> edges;
  vector<vector<int>> r_edges;
  SCC(int n): n(n), edges(n), r_edges(n) {}
  void insert_edge(int u, int v) {
    edges[u].push_back(v);
    r_edges[v].push_back(u);
  }
  void _insert_stack(int u, stack<int> &s, vector<bool> &vs) {
    vs[u] = true;
    for (int v: edges[u]) {
      if (vs[v]) continue;
      _insert_stack(v, s, vs);
    }
    s.push(u);
  }
  void _gather(int u, vector<int> &vi, vector<bool> &vs) {
    vs[u] = true;
    vi.push_back(u);
    for (int v: r_edges[u]) {
      if (vs[v]) continue;
      _gather(v, vi, vs);
    }
  }
  vector<vector<int>> query() {
    vector<vector<int>> res;
    stack<int> s;
    vector<bool> vs(n, false);
    for (int i = 0; i < n; i++) {
      if (vs[i]) continue;
      _insert_stack(i, s, vs);
    }
    fill(vs.begin(), vs.end(), false);
    while (!s.empty()) {
      int u = s.top(); s.pop();
      if (vs[u]) continue;
      vector<int> n_vi;
      _gather(u, n_vi, vs);
      res.push_back(n_vi);
    }
    return res;
  }
};
