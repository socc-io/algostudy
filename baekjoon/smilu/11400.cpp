#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 100010;

int n, m;
vector<pair<int,int>> ans;
vector<int> adj[MAX_N];
vector<int> bcc[MAX_N];
int dfn[MAX_N], dfn_piv;
int low[MAX_N];
int color_piv;
bool vis[MAX_N];

void add_edge(int a, int b) {
  if (a > b) swap(a, b);
  ans.emplace_back(a, b);
}

void init_tree(int u, int p) {
  dfn[u] = ++dfn_piv;
  low[u] = dfn[u];
  for (int v: adj[u]) {
    if (v == p) continue;
    if (dfn[v]) {
      low[u] = min(low[u], dfn[v]);
    } else {
      init_tree(v, u);
      low[u] = min(low[u], low[v]);
    }
  }
}

void set_color(int u, int c = 0) {
  if (c) bcc[u].push_back(c);
  vis[u] = true;
  for (int v: adj[u]) {
    if (vis[v]) continue;
    if (dfn[u] <= low[v]) {
      bcc[u].push_back(++color_piv);
      if (dfn[u] != low[v]) add_edge(u, v);
      set_color(v, color_piv);
    } else {
      set_color(v, c);
    }
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  init_tree(1, 0);
  set_color(1);

  // for (int i = 1; i <= n; i++) {
  //   cout << i << ": ";
  //   for (int v: bcc[i]) cout << v << ' ';
  //   cout << '\n';
  // }

  sort(ans.begin(), ans.end());
  auto ae = unique(ans.begin(), ans.end());
  cout << distance(ans.begin(), ae) << '\n';
  for (auto it = ans.begin(); it != ae; it++) {
    cout << it->first << ' ' << it->second << '\n';
  }
}
