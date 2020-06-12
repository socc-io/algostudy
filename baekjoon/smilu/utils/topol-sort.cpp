#include <bits/stdc++.h>
using namespace std;

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