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

int solve() {
    int n, m;
    cin >> n >> m;
    
    BipartiteMatch match(n, n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        match.add_edge(u, v);
    }

    return match.execute();
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        cout << solve() << '\n';
    }
}
