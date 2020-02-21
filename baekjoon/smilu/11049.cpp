#include <cstdio>

#define INF 0x7FFFFFF0

int n;
int v[501];
int dp[501][501];

int get(int x, int y) {
  if (x+1 >= y) return 0;
  int& res = dp[x][y];
  if (res != INF) return res;
  for (int z = x+1; z < y; z++) {
    int nv = get(x, z) + get(z, y) + v[x] * v[z] * v[y];
    if (nv < res) res = nv;
  }
  return res;
}

int main(void)
{
  for (int i = 0; i < 501; i++) {
    for(int j = 0; j < 501; j++) {
      dp[i][j] = INF;
    }
  }

  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int a, b; scanf("%d%d", &a, &b);
    if (i == 0) v[0] = a;
    v[i+1] = b;
  }

  printf("%d", get(0, n));
}
