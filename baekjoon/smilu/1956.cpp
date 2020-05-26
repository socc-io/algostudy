#include <bits/stdc++.h>
using namespace std;

int n, m;

int dist[401][401];

int main(void)
{
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n >> m;
  memset(dist, 0x3f, sizeof(dist));
  for (int i = 0; i < m; i++) {
    int a, b, w; cin >> a >> b >> w;
    dist[a][b] = w;
  }
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        int nd = dist[i][k] + dist[k][j];
        if (nd < dist[i][j]) {
          dist[i][j] = nd;
        }
      }
    }
  }
  int ans = 0x3f3f3f3f;
  for (int i = 1; i <= n; i++) {
    for (int j = i+1; j <= n; j++) {
      ans = min(ans, dist[i][j] + dist[j][i]);
    }
  }
  cout << (ans == 0x3f3f3f3f ? -1 : ans) << '\n';
}
