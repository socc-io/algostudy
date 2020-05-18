#include <cstdio>
#include <cstring>

int tile[9][9];

void check_row(bool *s, int index) {
  for (int i = 0; i < 9; i++) {
    s[tile[index][i]] = true;
  }
}

void check_col(bool *s, int index) {
  for (int i = 0; i < 9; i++) {
    s[tile[i][index]] = true;
  }
}

void check_sqr(bool *s, int cx, int cy) {
  cx*=3; cy*=3;
  for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) {
    s[tile[cx+i][cy+j]] = true;
  }
}

bool dfs(int x, int y) {
  if (x == 9) return true;
  bool s[10];
  int nx = x + (y+1)/9, ny = (y+1)%9;
  if (tile[x][y] != 0) return dfs(nx, ny);
  memset(s, 0x00, sizeof(s));
  check_row(s, x);
  check_col(s, y);
  check_sqr(s, x/3, y/3);
  for (int i = 1; i <= 9; i++) {
    if (s[i]) continue;
    tile[x][y] = i;
    if (dfs(nx, ny)) return true;
  }
  tile[x][y] = 0;
  return false;
}

int main(void)
{
  for (int i = 0; i < 9; i++) for (int j = 0; j < 9; j++) {
    scanf("%d", &tile[i][j]);
  }
  dfs(0, 0);
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      printf("%d ", tile[i][j]);
    } puts("");
  }
}
