#include <cstdio>
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

int main(void)
{
  int v, e;
  scanf("%d%d", &v, &e);
  SCC scc(v);
  for (int i = 0; i < e; i++) {
    int x, y;
    scanf("%d%d", &x, &y); 
    scc.insert_edge(x-1, y-1);
  }
  vector<vector<int>> ans = scc.query();
  
  for (auto &vi: ans) sort(vi.begin(), vi.end());
  sort(ans.begin(), ans.end());

  printf("%lu\n", ans.size());
  for (auto &vi: ans) {
    for (int v: vi) {
      printf("%d ", v+1);
    } puts("-1");
  }
}
