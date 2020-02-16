#include <cstdio>

char tile[128][128];
int N;

typedef unsigned long long llu;

llu count(int x1, int y1, int x2, int y2) {
  if (x2 == x1 + 1 && y2 == y1 + 1) {
    return 4294967296LL - 4294967295LL * tile[x1][y1];
  }
  int xm = (x1 + x2) / 2;
  int ym = (y1 + y2) / 2;
  llu res = count(x1, y1, xm, ym)
          + count(x1, ym, xm, y2)
          + count(xm, y1, x2, ym)
          + count(xm, ym, x2, y2);
  if (res == 17179869184LL) return 4294967296LL; // white full
  else if (res == 4) return 1; // blue full
  return res;
}

int main(void)
{
  scanf("%d", &N);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      int a; scanf("%d", &a);
      tile[i][j] = a;
    }
  }
  llu res = count(0, 0, N, N);
  printf("%llu\n%llu", res >> 32, res & 0xFFFFFFFF);
}