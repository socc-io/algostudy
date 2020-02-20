#include <cstdio>

int n, m;
bool c[100][100];
bool air[100][100];

const int dd[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

bool outbound(int x, int y) {
  if (x < 0 || x >= n || y < 0 || y >= m) return true;
  return false;
}

void clear(bool buf[][100]) {
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      buf[i][j] = false;
    }
  }
}

void find_air(int x, int y) {
  air[x][y] = true;
  for (int i = 0; i < 4; i++) {
    int nx = x + dd[i][0];
    int ny = y + dd[i][1];
    if (outbound(nx, ny)) continue;
    if (c[nx][ny]) continue;
    if (air[nx][ny]) continue;
    find_air(nx, ny);
  }
}

int time() {
  clear(air);
  find_air(0, 0);
  int erase = 0;
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      if (c[i][j] == 0) continue;
      int cnt = 0;
      for (int di = 0; di < 4; di++) {
        int nx = i + dd[di][0];
        int ny = j + dd[di][1];
        if (outbound(nx, ny)) continue;
        if (!air[nx][ny]) continue;
        ++cnt;
      }
      if (cnt >= 2) {
        c[i][j] = 0;
        ++erase;
      }
    }
  }
  return erase;
}

int main(void)
{
  scanf("%d%d", &n, &m);
  int cnt = 0;
  int t = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int tmp; scanf("%d", &tmp);
      c[i][j] = tmp ? true : false;
      if (tmp == 1) ++cnt;
    }
  }
  while(cnt) {
    cnt -= time();
    ++t;
  }
  printf("%d", t);
}