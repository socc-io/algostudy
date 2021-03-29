#include <bits/stdc++.h>
using namespace std;

bool vs[501];
vector<int> adj[501];

bool dfs(int u, int p) {
  vs[u] = true;
  for (int v: adj[u]) {
    if (v == p) continue;
    if (vs[v]) return false;
    if (!dfs(v, u)) return false;
  }
  return true;
}

int solve(int n, int m) {
  memset(vs, 0x00, sizeof(vs));
  for (int i = 0; i < 501; i++) adj[i].clear();
  for (int i = 0; i < m; i++) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (vs[i]) continue;
    ans += dfs(i, 0);
  }
  return ans;
}

void print_case(int cn, int ans) {
  cout << "Case " << cn << ": ";
  if (ans == 0) cout << "No trees.\n";
  else if (ans == 1) cout << "There is one tree.\n";
  else cout << "A forest of " << ans << " trees.\n";
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t = 0, n, m;
  while (cin >> n >> m) {
    if (n == 0 && m == 0) break;
    print_case(++t, solve(n, m));
  }
}
