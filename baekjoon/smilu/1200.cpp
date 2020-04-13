#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

#define INF 0x7F7F7F7F7F7F7F7F

typedef long long lld;

lld tm[18][18]; // time table
lld tms[18][18]; // sum of time table [(0, 0),(i, j)]
int n, m, r, s;
lld dp[18][18][24310]; // row[0,i], using j horizontal dividers, column division case index
int dvs[24310]; // column division cases
int num_dvs;

lld get_tms(int x, int y) {
  // get sum of [(0, 0), (x, y)]
  if (x < 0 || y < 0) return 0;
  return tms[x][y];
}

inline lld get_sum_range(int x1, int y1, int x2, int y2) {
  // get sum of [(x1, y1), (x2, y2))
  return get_tms(x2-1, y2-1)
       - get_tms(x2-1, y1-1)
       - get_tms(x1-1, y2-1)
       + get_tms(x1-1, y1-1);
}

lld get_max(int begin_x, int end_x, int dv) {
  // get maximum local sum in [(begin_x, 0), (end_x, m)) when dividing with division case 'dv'
  lld mls = -1; // max local sum
  lld ls = 0; // local sum
  int prev_x = 0;
  for (int i = 0; i < m; i++) {
    if (dv & (1 << i)) {
      ls = get_sum_range(begin_x, prev_x, end_x, i+1);
      mls = max(mls, ls);
      prev_x = i + 1;
    }
  }
  return mls;
}

int main(void)
{
  scanf("%d%d%d%d", &n, &m, &r, &s);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%lld", &tm[i][j]);
    }
  }

  /* calculate sum of range of tm  */
  tms[0][0] = tm[0][0];
  for (int i = 1; i < n; i++) tms[i][0] = tms[i-1][0] + tm[i][0];
  for (int i = 1; i < m; i++) tms[0][i] = tms[0][i-1] + tm[0][i];
  for (int i = 1; i < n; i++) {
    for (int j = 1; j < m; j++) {
      tms[i][j] = tms[i-1][j] + tms[i][j-1] - tms[i-1][j-1] + tm[i][j];
    }
  }

  /* get column division cases */
  vector<bool> dvf(m - 1, false);
  for (int i = 0; i < s; i++) dvf[m-2-i] = true;
  do {
    int dv = (1 << (m - 1));
    for (int i = 0; i < m - 1; i++) dv |= ((int)dvf[i]) << i;
    dvs[num_dvs++] = dv;
  } while (next_permutation(dvf.begin(), dvf.end()));

  /* calculate dp table */
  lld ans = INF;
  memset(dp, 0x7F, sizeof(dp));
  for (int dvi = 0; dvi < num_dvs; dvi++) {
    int dv = dvs[dvi];
    for (int x = 0; x < n; x++) {
      dp[x][0][dvi] = get_max(0, x+1, dv);
      int c_end = min(x, r) + 1;
      for (int c = 1; c < c_end; c++) {
        lld &res = dp[x][c][dvi];
        for (int px = 0; px < x; px++) {
          lld p = dp[px][c-1][dvi];
          lld a = get_max(px + 1, x + 1, dv);
          res = min(res, max(a, p));
        }
      }
    }
    ans = min(ans, dp[n-1][r][dvi]);
  }
  
  printf("%lld\n", ans);
}
