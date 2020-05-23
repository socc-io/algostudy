#include <bits/stdc++.h>
using namespace std;

const int cost[5][5] = {
  {1,2,2,2,2},
  {2,1,3,4,3},
  {2,3,1,3,4},
  {2,4,3,1,3},
  {2,3,4,3,1},
};
const int inf = 0x3f3f3f3f;

int n;
int f[100010];
int dp[100010][5][5];

int get_dp(int i, int a, int b) {
  if (i == -1) {
    if (a == 0 && b == 0) return 0;
    return inf;
  }
  // if (i >= 2 && (a == 0 || b == 0)) return inf;
  if (a == b) return inf;
  if (a != f[i] && b != f[i]) return inf;
  int &ret = dp[i][a][b];
  if (ret != -1) return ret;
  ret = inf;
  for (int p = 0; p < 5; p++) {
    ret = min(ret, get_dp(i-1, p, b) + cost[p][a]);
    ret = min(ret, get_dp(i-1, a, p) + cost[p][b]);
  }
  return ret;
}

int main(void)
{
  memset(dp, 0xff, sizeof(dp));
  while (1) {
    int tmp; scanf("%d", &tmp);
    if (tmp == 0) break;
    f[n++] = tmp;
  }
  int ans = inf;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      ans = min(ans, get_dp(n-1, i, j));
    }
  }
  printf("%d\n", ans);
}
