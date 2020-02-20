#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

const int shapes[3][4][2] = {
  {{0,0},{0,-1},{0,0},{0,0}},
  {{0,0},{-1,0},{0,0},{0,0}},
  {{0,0},{0,-1},{-1,0},{-1,-1}},
};
const int shape_sizes[3] = {2, 2, 4};
const int prev_state_diffs[3][3][3] = {
  {{0,-1,0},{0,-1,2},{0,0,0}},
  {{-1,0,1},{-1,0,2},{0,0,0}},
  {{-1,-1,0},{-1,-1,1},{-1,-1,2}},
};
const int prev_state_diff_num[3] = {2, 2, 3};

int n; // 3 <= n <= 16
char tile[16][16];
int mem[16][16][3];

bool check(int x, int y, int t) {
  for (int i = 0; i < shape_sizes[t]; i++) {
    int nx = x + shapes[t][i][0];
    int ny = y + shapes[t][i][1];
    if (nx < 0 || ny < 0) return false;
    if (tile[nx][ny]) return false;
  }
  return true;
}

int get(int x, int y, int t) {
  int &res = mem[x][y][t];
  if (res != -1) return res;
  if (!check(x, y, t)) {
    res = 0;
    return res;
  }
  res = 0;
  for (int i = 0; i < prev_state_diff_num[t]; i++) {
    int nx = x + prev_state_diffs[t][i][0];
    int ny = y + prev_state_diffs[t][i][1];
    int nt = prev_state_diffs[t][i][2];
    res += get(nx, ny, nt);
  }
  return res;
}

int main(void)
{
  for (int i = 0; i < 16; i++) for (int j = 0; j < 16; j++) {
    for (int k = 0; k < 3; k++) mem[i][j][k] = -1;
  }
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int tmp; scanf("%d", &tmp);
      tile[i][j] = (char)tmp;
    }
  }
  mem[0][1][0] = 1;
  int res = get(n-1,n-1,0) + get(n-1,n-1,1) + get(n-1,n-1,2);
  printf("%d", res);
}