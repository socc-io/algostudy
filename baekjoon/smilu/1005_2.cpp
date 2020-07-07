#include <bits/stdc++.h>
using namespace std;

int solve() {
  int n, k; cin >> n >> k;
  vector<int> d(n+1);
  vector<vector<int>> adj(n+1);
  vector<int> nin(n+1);
  vector<int> st(n+1);
  for (int i = 1; i <= n; i++) cin >> d[i];
  while (k--) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    nin[b]++;
  }
  int w; cin >> w;
  queue<int> q;
  for (int i = 1; i <= n; i++) if (nin[i] == 0) q.push(i);
  while (!q.empty()) {
    int u = q.front(); q.pop();
    int nst = st[u] + d[u];
    for (int v: adj[u]) {
      nin[v]--;
      st[v] = max(st[v], nst);
      if (nin[v] == 0) q.push(v);
      if (v == w && nin[w] == 0) {
        while (!q.empty()) q.pop();
        break;
      }
    }
  }
  return st[w] + d[w];
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t;
  while (t--) cout << solve() << '\n';
}
