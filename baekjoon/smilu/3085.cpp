#include <bits/stdc++.h>
using namespace std;

int n;
char tile[51][51];

int check_col(int ci, char c) {
  int ret = 0, cnt = 0;
  for (int i = 0; i < n; i++) {
    if (tile[i][ci] == c) ret = max(ret, ++cnt);
    else cnt = 0;
  }
  return ret;
}

int check_row(int ri, char c) {
  int ret = 0, cnt = 0;
  for (int i = 0; i < n; i++) {
    if (tile[ri][i] == c) ret = max(ret, ++cnt);
    else cnt = 0;
  }
  return ret;
}

int check_color(char c) {
  int ret = 0;
  for (int i = 0; i < n; i++) {
    ret = max(ret, check_row(i, c));
    ret = max(ret, check_col(i, c));
  }
  return ret;
}

int check_board() {
  static const char* colors = "CPZY";
  int ret = 0;
  for (int i = 0; i < 4; i++) {
    ret = max(ret, check_color(colors[i]));
  }
  return ret;
}

int main(void)
{
  cin >> n;
  for (int i = 0; i < n; i++) scanf("%s", tile[i]);
  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (j+1 < n) {
        swap(tile[i][j], tile[i][j+1]);
        ans = max(ans, check_board());
        swap(tile[i][j], tile[i][j+1]);
      }
      if (i+1 < n) {
        swap(tile[i][j], tile[i+1][j]);
        ans = max(ans, check_board());
        swap(tile[i][j], tile[i+1][j]);
      }
    }
  }
  printf("%d\n", ans);
}

