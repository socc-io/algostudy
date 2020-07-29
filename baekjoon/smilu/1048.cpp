#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int mod = 1000000007;

int n, m, l, len;
char target[51];
char tile[301][301];

ll cnt[300][300];
ll acc[301][301];
ll cnt2[300][300];

void update_acc() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      acc[i][j] = (acc[i-1][j] + acc[i][j-1] - acc[i-1][j-1] + cnt[i-1][j-1]) % mod;
    }
  }
}

ll rect_acc(int x1, int y1, int x2, int y2) {
  x1 = max(x1, 0);
  x2 = min(x2, n-1) + 1;
  if (x1 >= x2) return 0;
  y1 = max(y1, 0);
  y2 = min(y2, m-1) + 1;
  if (y1 >= y2) return 0;
  return (acc[x2][y2] - acc[x1][y2] - acc[x2][y1] + acc[x1][y1]) % mod;
}

ll scan(int x, int y) {
  return (rect_acc(0, 0, x-2, y-3) +
  rect_acc(0, y-2, x-3, y-2) +
  rect_acc(0, y+2, x-3, m-1) +
  rect_acc(x-2, y+3, x-2, m-1) +
  rect_acc(x+2, 0, n-1, y-3) +
  rect_acc(x+3, y-2, n-1, y-2) +
  rect_acc(x+2, y+3, n-1, m-1) +
  rect_acc(x+3, y+2, n-1, y+2)) % mod;
}

int solve() {
  for (int ti = len-1; ti >= 0; ti--) {
    const char tc = target[ti];
    for (int x = 0; x < n; x++) {
      for (int y = 0; y < m; y++) {
        const char ch = tile[x][y];
        if (ch == tc) {
          cnt2[x][y] = scan(x, y) + (ti == len-1 ? 1 : 0);
        } else {
          cnt2[x][y] = 0;
        }
      }
    }
    memcpy(cnt, cnt2, sizeof(cnt));
    update_acc();
  }
  ll ans = 0;
  for (int x = 0; x < n; x++) {
    for (int y = 0; y < m; y++) {
      ans += cnt[x][y];
    }
  }
  while (ans < 0) ans += mod;
  return ans % mod;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n >> m >> l;
  cin >> target;
  len = strlen(target);
  for (int i = 0; i < n; i++) cin >> tile[i];
  cout << solve() << '\n';
}
