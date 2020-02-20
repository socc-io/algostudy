#include <cstdio>

#define MOD 1000000007

int d;
int es[8][4] = {
  {1, 5, -1, -1},
  {0, 2, 5, -1},
  {1, 3, 5, 6},
  {2, 4, 6, -1},
  {3, 7, -1, -1},
  {0, 1, 2, 6},
  {2, 3, 5, 7},
  {4, 6, -1, -1},
};
int ess[8] = {2, 3, 4, 3, 2, 4, 4, 2};
int dp[100001][8];

int main(void)
{
  scanf("%d", &d);
  dp[0][0] = 1;
  for (int t = 1; t <= d; t++) {
    for (int i = 0; i < 8; i++) {
      int nv = 0;
      for (int vi = 0; vi < ess[i]; vi++) {
        int v = es[i][vi];
        nv = (nv + dp[t-1][v]) % MOD;
      }
      dp[t][i] = nv;
    }
  }
  printf("%d", dp[d][0]);
}