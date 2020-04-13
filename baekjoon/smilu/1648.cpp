#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define MOD 9901

int n, m, nm, m1;
int dp[14*14][1<<14];

int gdp(int i, int j) {
  if (i == nm && j == 0) return 1;
  if (i >= nm) return 0;

  int &res = dp[i][j];
  if (res != -1) return res;
  
  if (j & 1) {
    res = gdp(i + 1, j >> 1);
  } else {
    res = gdp(i + 1, (j >> 1) | (1 << m1));
    if ((i % m) != m1 && (j & 2) == 0) {
      res += gdp(i + 2, j >> 2);
    }
    res %= MOD;
  }

  return res;
}

int main(void)
{
  memset(dp, 0xFF, sizeof(dp));
  scanf("%d%d", &n, &m);
  nm = n * m;
  m1 = m - 1;
  printf("%d\n", gdp(0, 0));
}
