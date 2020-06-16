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

const int dd[6][2] = {
  {-1,-1},{-1,1},
  { 0,-1},{ 0,1},
  { 1,-1},{ 1,1},
};

int solve() {
  int n, m; cin >> n >> m;
  vector<string> tile(n);
  for (string &s: tile) cin >> s;
  int Lw = (m+1)/2;
  int Rw = m/2;
  BipartiteMatch bm(n*Lw, n*Rw);
  for (int x = 0; x < n; x++) {
    for (int y = 0; y < m; y += 2) {
      if (tile[x][y] == 'x') continue;
      for (int di = 0; di < 6; di++) {
        int nx = x + dd[di][0], ny = y + dd[di][1];
        if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
        if (tile[nx][ny] == 'x') continue;
        int L = x*Lw + y/2;
        int R = nx*Rw + ny/2;
        bm.add_edge(L, R);
      }
    }
  }
  int cnt_dot = 0;
  for (int x = 0; x < n; x++) {
    for (char ch: tile[x]) cnt_dot += (ch == '.');
  }
  return cnt_dot - bm.execute();
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t;
  while (t--) cout << solve() << '\n';
}
