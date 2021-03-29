#include <bits/stdc++.h>
using namespace std;

int v, e;

vector<int> nei[20020];
int grp[20020];

bool propagate(int u, int g) {
  if (grp[u]) return grp[u] == g;
  grp[u] = g;
  for (int v: nei[u]) {
    if (!propagate(v, 3-g)) return false;
  }
  return true;
}

bool solve() {
  cin >> v >> e;
  for (int i = 0; i < 20020; i++) nei[i].clear();
  memset(grp, 0x00, sizeof(grp));
  for (int i = 0; i < e; i++) {
    int a, b; cin >> a >> b;
    nei[a].push_back(b);
    nei[b].push_back(a);
  }

  for (int i = 1; i <= v; i++) {
    if (grp[i]) continue;
    if (!propagate(i, 1)) return false;
  }
  
  return true;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t;
  while (t--) {
    cout << (solve() ? "YES\n" : "NO\n");
  }
}
