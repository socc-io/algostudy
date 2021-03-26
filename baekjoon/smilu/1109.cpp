#include <bits/stdc++.h>
using namespace std;

const int dd[4][2] = {{-1,0},{1,0},{0,1},{0,-1}};
const int gd[8][2] = {{-1,0},{1,0},{0,1},{0,-1},{-1,-1},{-1,1},{1,-1},{1,1}};

int n, m;
char tile[55][55];
int grp[55][55];
bool chk[55][55];
int max_grp;
bool g_chk[3025];
int lev[3025];
int cnt_lev[3025];

void visit(int ix, int iy) {
  for (int di = 0; di < 4; di++) {
    int nx = ix + dd[di][0], ny = iy + dd[di][1];
    if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
    if (tile[nx][ny] != 'x') continue;
    g_chk[grp[nx][ny]] = true;
  }
  for (int di = 0; di < 4; di++) {
    int nx = ix + dd[di][0], ny = iy + dd[di][1];
    if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
    if (tile[nx][ny] != '.' || chk[nx][ny]) continue;
    chk[nx][ny] = true;
    visit(nx, ny);
  }
}

void set_grp(int ix, int iy, int gn) {
  grp[ix][iy] = gn;
  for (int di = 0; di < 8; di++) {
    int nx = ix + gd[di][0], ny = iy + gd[di][1];
    if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
    if (grp[nx][ny] != 0) continue;
    if (tile[nx][ny] != 'x') continue;
    grp[nx][ny] = gn;
    set_grp(nx, ny, gn);
  }
}

int main() {
  cin.tie(0); ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> (tile[i+1] + 1);
  n++;n++;m++;m++;
  for (int i = 0; i < m; i++) {
    tile[0][i] = '.';
    tile[n-1][i] = '.';
  }
  for (int i = 0; i < n; i++) {
    tile[i][0] = '.';
    tile[i][m-1] = '.';
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grp[i][j] == 0 && tile[i][j] == 'x') {
        set_grp(i, j, ++max_grp);
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (tile[i][j] != '.' || chk[i][j]) continue;
      memset(g_chk, 0x00, sizeof(g_chk));
      chk[i][j] = true;
      visit(i, j);
      vector<int> gs;
      for (int i = 1; i <= max_grp; i++) if (g_chk[i]) gs.push_back(i);
      int max_lev = 0;
      for (int g: gs) if (lev[g] > 0) max_lev = max(max_lev, lev[g]);
      for (int g: gs) if (lev[g] == 0) lev[g] = max_lev + 1;
    }
  }
  int max_lev = 0; for (int i = 1; i <= max_grp; i++) max_lev = max(max_lev, lev[i]);
  for (int i = 1; i <= max_grp; i++) cnt_lev[lev[i]]++;
  for (int i = 1; i <= max_lev; i++) cout << cnt_lev[i] << ' ';
}
