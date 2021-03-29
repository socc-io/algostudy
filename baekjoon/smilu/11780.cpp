#include <bits/stdc++.h>
using namespace std;

const int inf = 0x3f3f3f3f;

int n, m;

int dp[100][100];
int rt[100][100];

int escape_inf(int v) {
  return v == inf ? 0 : v;
}

void track_rts(int f, int t, vector<int> & rts) {
  if (f == t) return;
  if (rt[f][t] == t) {
    rts.push_back(t);
    return;
  }
  track_rts(f, rt[f][t], rts);
  track_rts(rt[f][t], t, rts);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n >> m;
  memset(dp, 0x3f, sizeof(dp));
  for (int i = 0; i < n; i++) dp[i][i] = 0;
  for (int i = 0; i < m; i++) {
    int a, b, c; cin >> a >> b >> c;
    --a; --b;
    if (c < dp[a][b]) {
      dp[a][b] = c;
      rt[a][b] = b;
    }
  }
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        int nr = dp[i][k] + dp[k][j];
        if (nr < dp[i][j]) {
          dp[i][j] = nr;
          rt[i][j] = k;
        }
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << escape_inf(dp[i][j]) << ' ';
    }
    cout << '\n';
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (dp[i][j] == inf) {
        cout << "0\n";
        continue;
      }
      vector<int> rts;
      if (i != j) rts.push_back(i);
      track_rts(i, j, rts);
      cout << rts.size() << ' ';
      for (int rti: rts) cout << rti+1 << ' ';
      cout << '\n';
    }
  }
}
