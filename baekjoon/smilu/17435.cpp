#include <bits/stdc++.h>
using namespace std;

int nxt[200001][19];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int m; cin >> m;
  for (int i = 1; i <= m; i++) cin >> nxt[i][0];
  for (int i = 1; i < 19; i++) {
    for (int j = 1; j <= m; j++) {
      nxt[j][i] = nxt[nxt[j][i-1]][i-1];
    }
  }
  int q; cin >> q;
  while (q--) {
    int n, x; cin >> n >> x;
    for (int i = 0; i < 19; i++) {
      if (n&1) x = nxt[x][i];
      n >>= 1;
    }
    cout << x << '\n';
  }
}
