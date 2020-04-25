#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int dp[50][2500];

int dfs(int n, int s) {
  if (s < 0) return 0;
  if (n == 0) return s==0;
  int &ret = dp[n][s];
  if (ret != -1) return ret;

  for (int k = 1; k <= n; k++) {
    int m = k*(k+1)/2;
    if (dfs(n-k,s-m)) return ret = 1;
  }

  return ret = 0;
}

int main(void)
{
  memset(dp, 0xFF, sizeof(dp));
  int n, s;
  scanf("%d%d", &n, &s);
  printf("%d\n", dfs(n-2, s));
}
