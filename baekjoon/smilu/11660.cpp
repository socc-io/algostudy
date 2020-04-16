#include <cstdio>

int s[1024][1024];

int main(void)
{
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int tmp; scanf("%d", &tmp);
      s[i][j] += tmp;
      if (i > 0) {
        s[i][j] += s[i-1][j];
        if (j > 0) {
          s[i][j] -= s[i-1][j-1];
        }
      }
      if (j > 0) s[i][j] += s[i][j-1];
    }
  }
  for (int i = 0; i < m; i++) {
    int x1, x2, y1, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    x1 -= 2;
    y1 -= 2;
    x2 -= 1;
    y2 -= 1;
    int res = s[x2][y2];
    if (x1 >= 0) res -= s[x1][y2];
    if (y1 >= 0) res -= s[x2][y1];
    if (x1 >= 0 && y1 >= 0) res += s[x1][y1];
    printf("%d\n", res);
  }
}
