#include <bits/stdc++.h>
using namespace std;

#define MAX_N 10010

int n, m;
vector<int> adj[MAX_N];

int dfn[MAX_N], dfn_piv;
int low[MAX_N];
bool vis[MAX_N];
int cnt[MAX_N];

void init_tree(int u, int p) {
  dfn[u] = ++dfn_piv;
  low[u] = dfn[u];
  for (int v: adj[u]) {
    if (v == p) continue;
    if (dfn[v] == 0) {
      init_tree(v, u);
      low[u] = min(low[u], low[v]);
    } else {
      low[u] = min(low[u], dfn[v]);
    }
  }
}

void count_bcc(int u, int c = 0) {
  if (c) cnt[u]++;
  vis[u] = 1;
  for (int v: adj[u]) {
    if (vis[v]) continue;
    if (dfn[u] <= low[v]) cnt[u]++;
    count_bcc(v, 1);
  }
}

int main(void)
{
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  for (int i = 1; i <= n; i++) {
    if (dfn[i]) continue;
    init_tree(i, 0);
  }
  for (int i = 1; i <= n; i++) {
    if (vis[i]) continue;
    count_bcc(i);
  }
  vector<int> ans;
  for (int i = 1; i <= n; i++) {
    if (cnt[i] > 1) ans.push_back(i);
  }
  cout << ans.size() << '\n';
  for (int v: ans) cout << v << ' ';
}
