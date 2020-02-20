#include <cstdio>

int n;
char buf[101];
char sc[100][100]; // screen;
int gr[100][100]; // group;

int adj[][2] = {
  {1, 0},
  {-1, 0},
  {0, 1},
  {0, -1},
};

void assign_group(int x, int y, int g) {
  gr[x][y] = g;
  char color = sc[x][y];
  for (int i = 0; i < 4; i++) {
    int nx = x + adj[i][0];
    int ny = y + adj[i][1];
    if (nx < 0 || nx >= n) continue;
    if (ny < 0 || ny >= n) continue;
    if (gr[nx][ny] != 0) continue;
    if (color != sc[nx][ny]) continue;
    assign_group(nx, ny, g);
  }
}

int count() {
  int g = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (gr[i][j] == 0) {
        assign_group(i, j, g++);
      }
    }
  }
  return g - 1;
}

void gtor() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (sc[i][j] == 'G') {
        sc[i][j] = 'R';
      }
      gr[i][j] = 0;
    }
  }
}

int main(void)
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%s", buf);
    for (int j = 0; j < n; j++) {
      sc[i][j] = buf[j];
    }
  }

  int areas = count();
  gtor();
  int gr_areas = count();

  printf("%d %d", areas, gr_areas);
}