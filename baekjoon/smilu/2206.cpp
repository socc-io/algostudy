#include <cstdio>

#define INF 123456789

struct state {
  // int pl; // prev level
  // int px; // prev x
  // int py; // prev y
  int mc; // min cost
};

const int dd[4][2] = {
  {1,0},{-1,0},
  {0,1},{0,-1},
};

int n, m;
char tile[1000][1001];
state states[2][1000][1000];

void search(int cl, int cx, int cy, int cc) {
  state* s = &states[cl][cx][cy];
  if (s->mc <= cc) return;
  s->mc = cc;
  // printf("[%d,%d,%d]=%d\n", cl, cx, cy, cc);
  int nc = cc + 1;
  for (int di = 0; di < 4; di++) {
    int nx = cx + dd[di][0];
    int ny = cy + dd[di][1];
    if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
    int nl = cl + tile[nx][ny];
    if (nl >= 2) continue;
    search(nl, nx, ny, nc);
  }
}

int main(void)
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    scanf("%s", tile[i]);
    for (int j = 0; j < m; j++) {
      tile[i][j] -= '0';
    }
  }
  for (int i = 0; i < 2; i++) for (int j = 0; j < 1000; j++)
    for (int k = 0; k < 1000; k++) states[i][j][k].mc = INF;
  search(0, 0, 0, 1);

  int min = INF;
  for (int i = 0; i < 2; i++) {
    int c = states[i][n-1][m-1].mc;
    if (c < min) min = c;
  }
  printf("%d", min == INF ? -1 : min);
}