#include <bits/stdc++.h>
using namespace std;

int sz[100001];
vector<int> adj[100001];

void init_tree(int u, int p) {
  sz[u] = 1;
  for (int v: adj[u]) {
    if (v == p) continue;
    init_tree(v, u);
    sz[u] += sz[v];
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int n, r, q;
  cin >> n >> r >> q;
  for (int i = 1; i < n; i++) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  init_tree(r, 0);
  while (q--) {
    int u; cin >> u;
    cout << sz[u] << '\n';
  }
}
