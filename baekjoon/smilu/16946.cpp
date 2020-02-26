#include <cstdio>

const int dd[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

int n, m;
char line_buf[1001];
bool wall[1000][1000];
int   grp[1000][1000];
int   ans[1000][1000];
int g_size[1000000];
int g_index = 1;

bool outbound(int x, int y) {
  return x < 0 || x >= n || y < 0 || y >= m;
}

int get_ans(int x, int y) {
  if (wall[x][y] == false) return 0;
  int met_grps[4];
  int met_index = 0;
  int ans = 0;
  for (int di = 0; di < 4; di++) {
    int nx = x + dd[di][0], ny = y + dd[di][1];
    if (outbound(nx, ny)) continue;
    if (wall[nx][ny]) continue;
    int gv = grp[nx][ny];
    bool met = false;
    for (int i = 0; i < met_index; i++) {
      if (met_grps[i] == gv) {
        met = true;
        break;
      }
    }
    if (met) continue;
    met_grps[met_index++] = gv;
    ans += g_size[gv];
  }
  return ans + 1;
}

void assign_group(int x, int y, int gv) {
  grp[x][y] = gv;
  g_size[gv]++;
  for (int di = 0; di < 4; di++) {
    int nx = x + dd[di][0], ny = y + dd[di][1];
    if (outbound(nx, ny)) continue;
    if (wall[nx][ny]) continue;
    if (grp[nx][ny] != 0) continue;
    assign_group(nx, ny, gv);
  }
}

int main(void)
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    scanf("%s", line_buf);
    for (int j = 0; j < m; j++) {
      wall[i][j] = line_buf[j] == '1';
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grp[i][j] != 0) continue;
      if (wall[i][j]) continue;
      assign_group(i, j, g_index++);
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%d", get_ans(i, j) % 10);
    } puts("");
  }
}
