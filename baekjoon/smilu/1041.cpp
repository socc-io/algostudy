#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n;
ll vs[6];

const bool adj[6][6] = {
  {0, 1, 1, 1, 1, 0},
  {1, 0, 1, 1, 0, 1},
  {1, 1, 0, 0, 1, 1},
  {1, 1, 0, 0, 1, 1},
  {1, 0, 1, 1, 0, 1},
  {0, 1, 1, 1, 1, 0},
};

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  ll n; cin >> n;
  for (int i = 0; i < 6; i++) cin >> vs[i];
  ll bs3 = 0x3f3f3f3f;
  for (int i = 0; i < 6; i++) {
    for (int j = i+1; j < 6; j++) {
      if (!adj[i][j]) continue;
      for (int k = j+1; k < 6; k++) {
        if (!adj[j][k] || !adj[i][k]) continue;
        bs3 = min(bs3, vs[i] + vs[j] + vs[k]);
      }
    }
  }
  ll bs2 = 0x3f3f3f3f;
  for (int i = 0; i < 6; i++) {
    for (int j = i+1; j < 6; j++) {
      if (!adj[i][j]) continue;
      bs2 = min(bs2, vs[i] + vs[j]);
    }
  }
  ll bs1 = *min_element(vs, vs+6);
  if (n == 1) cout << (accumulate(vs, vs+6, 0) - *max_element(vs, vs+6));
  else {
    ll  ret  = (5*n*n - 16*n + 12) * bs1;
        ret += (8*n - 12) * bs2;
        ret += 4 * bs3;
    cout << ret;
  }
}
