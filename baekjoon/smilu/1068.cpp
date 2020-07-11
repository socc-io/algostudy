#include <bits/stdc++.h>
using namespace std;

int n, r;
int par[51];
vector<int> chd[51];

int count_leaf(int u) {
  const vector<int> &cs = chd[u];
  if (cs.size() == 0) return 1;
  int ret = 0;
  for (int v: cs) ret += count_leaf(v);
  return ret;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n;
  for (int i = 0; i < n; i++) cin >> par[i];
  const int root = find(par, par+n, -1) - par;
  cin >> r;
  if (r == root) { cout << "0"; return 0; }
  par[r] = -2;
  for (int i = 0; i < n; i++) if (par[i] >= 0) chd[par[i]].push_back(i);
  cout << count_leaf(root);
}
