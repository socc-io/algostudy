#include <cstdio>
#include <algorithm>
using namespace std;

int n, k;
int u[4001][4001];
int c[4001][4001];
int d[801][4001];

void dp(int l, int s, int e, int ps, int pe) {
  if (s > e) return;
  int m = (s+e)>>1, mv = -1, mp = -1;
  for (int p = ps; p <= min(m-1,pe); p++) {
    int tmp = d[l-1][p] + c[p+1][m];
    if (mv == -1 || tmp < mv) {
      mv = tmp;
      mp = p;
    }
  }
  d[l][m] = mv;
  if (s == e) return;
  dp(l, s, m-1, ps, mp);
  dp(l, m+1, e, mp, pe);
}

int main(void)
{
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      scanf("%d", &u[i][j]);
    }
  }
  for (int l = 2; l <= n; l++) {
    for (int s = 1; s <= n-l+1; s++) {
      int e = s + l - 1;
      c[s][e] = c[s][e-1]+c[s+1][e]-c[s+1][e-1]+u[s][e];
    }
  }
  for (int i = 1; i <= n; i++) {
    d[1][i] = c[1][i];
  }
  for (int i = 2; i <= k; i++) dp(i, 1, n, 1, n);
  printf("%d\n", d[k][n]);
}
