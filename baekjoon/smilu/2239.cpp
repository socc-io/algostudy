#include <cstdio>

int tile[9][9];

bool find(int x, int y) {
  if (x == 9) return true;
  int nx = x;
  int ny = y + 1;
  if (ny == 9) {
    ++nx;
    ny = 0;
  }
  if (tile[x][y]) return find(nx, ny); 
  bool ok[10];
  for (int i = 1; i < 10; i++) ok[i] = true;
  for (int i = 0; i < 9; i++) {
    ok[tile[x][i]] = false;
    ok[tile[i][y]] = false;
  }
  int bx = (x / 3) * 3;
  int by = (y / 3) * 3;
  for (int i = bx; i < bx + 3; i++) {
    for (int j = by; j < by + 3; j++) {
      ok[tile[i][j]] = false;
    }
  }
  for (int i = 1; i < 10; i++) {
    if (!ok[i]) continue;
    tile[x][y] = i;
    if (find(nx, ny)) return true;
  }
  tile[x][y] = 0;
  return false;
}

int main(void)
{
  char buf[10];
  for (int i = 0; i < 9; i++) {
    scanf("%s", buf);
    for (int j = 0; j < 9; j++) {
      tile[i][j] = buf[j] - '0';
    }
  }
  find(0, 0);
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      printf("%d", tile[i][j]);
    }
    puts("");
  }
}