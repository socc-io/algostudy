#include <bits/stdc++.h>
using namespace std;

int n, m;
int cnt_w, cnt_b;
int px, py;
char tile[500][501];
bool visit[500][500];

void dfs(int x, int y) {
  if (x < 0 || x >= n || y < 0 || y >= m) return;
  if (visit[x][y]) return;
  visit[x][y] = true;
  const char ch = tile[x][y];
  if (ch == '.') return;
  if (ch == 'W' && (x+px)%2 + (y+py)%2 != 0) return;
  if (ch == 'B' && (x+px)%2 + (y+py)%2 != 1) return;

  if (ch == 'W') ++cnt_w;
  if (ch == 'B') ++cnt_b;

  dfs(x-1, y);
  dfs(x+1, y);
  dfs(x, y+1);
  dfs(x, y-1);
}

bool solve() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> tile[i];

  for (px = 0; px < 2; px++) {
    for (py = 0; py < 2; py++) {
      memset(visit, 0x00, sizeof(visit));
      for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {
          cnt_w = cnt_b = 0;
          dfs(x, y);
          // cout << cnt_w << ", " << cnt_b << "\n";
          if (cnt_w != cnt_b) return false;
        }
      }
    }
  }
  return true;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t;
  while (t--) cout << (solve() ? "YES\n" : "NO\n");
}
