#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

#define LL_INF 0x7FFFFFFFFFFFFFFF

typedef long long lld;

int n;
lld cs[5001];
lld sum[5001]; // sum of [0, i)
lld dp[5000][5000]; // cost of [i, j]
int ks[5001][5001];

void solve() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &cs[i]);
    sum[i] = sum[i-1] + cs[i];
    dp[i-1][i] = 0;
    ks[i-1][i] = i;
  }
  for (int l = 2; l <= n; l++) {
    for (int i = 0; i <= n-l; i++) {
      int j = i + l;
      lld tmp = LL_INF;
      for (int k = ks[i][j-1]; k <= ks[i+1][j]; k++) {
        lld nxt = dp[i][k] + dp[k][j];
        if (nxt < tmp) {
          tmp = nxt;
          ks[i][j] = k;
        }
      }
      dp[i][j] = tmp + sum[j] - sum[i];
    }
  }
  printf("%lld\n", dp[0][n]);
}

int main(void) {
  int t; scanf("%d", &t);
  while(t--) solve();
}
