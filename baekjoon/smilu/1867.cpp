#include <bits/stdc++.h>
using namespace std;

class BipartiteMatch {
  int n;
  vector<vector<int>> adj;
  vector<int> mch;
  vector<bool> lck;
  bool augment(int u) {
    if (lck[u]) return false;
    lck[u] = true;
    for (int v: adj[u]) {
      if (mch[v] == -1 || augment(mch[v])) {
        mch[v] = u;
        return true;
      }
    }
    return false;
  }
public:
  BipartiteMatch(int n, int m): n(n), adj(n), mch(m), lck(n) {}
  void add_edge(int u, int v) {
    adj[u].push_back(v);
  }
  int execute() {
    int ret = 0;
    fill(mch.begin(), mch.end(), -1);
    for (int i = 0; i < n; i++) {
      fill(lck.begin(), lck.end(), false);
      ret += augment(i);
    }
    return ret;
  }
};

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n, m; cin >> n >> m;
  BipartiteMatch bm(n, m);
  while (m--) {
    int a, b; cin >> a >> b;
    bm.add_edge(a-1, b-1);
  }
  cout << bm.execute() << '\n';
}
