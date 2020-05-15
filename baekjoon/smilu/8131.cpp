#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX_N = 2020;
// const ll LL_INF = 0x3f3f3f3f3f3f3f3f;
const int L_INF = 0x3f3f3f3f;

int h, w;
ll k;
ll r_sum[MAX_N][MAX_N];
ll c_sum[MAX_N][MAX_N];

void transpose() {
  for (int x = 1; x < MAX_N; x++) {
    for (int y = 1; y < MAX_N; y++) {
      swap(r_sum[x][y], c_sum[x][y]);
    }
  }
  swap(h, w);
}

bool row_check(int x, int y1, int y2) {
  return r_sum[x][y2] - r_sum[x][y1-1] <= k;
}

bool col_check(int y, int x1, int x2) {
  return c_sum[y][x2] - c_sum[y][x1-1] <= k;
}

int dp[MAX_N][MAX_N];

ll get(int x1, int y1, int x2, int y2) {
  if (x1 > x2 || y1 > y2) return 0;

  ll alpha = 0;
  while (x1 <= x2 && row_check(x1, y1, y2)) {
    ++x1;
    ++alpha;
  }
  while (x1 <= x2 && row_check(x2, y1, y2)) {
    --x2;
    ++alpha;
  }

  if (x1 > x2) return alpha;
  
  if (dp[y1][y2] != L_INF) return dp[y1][y2] + alpha;
  ll ret = 0x3f3f3f3f3f3f3f3f;
  if (col_check(y1, x1, x2)) {
    ret = min(ret, get(x1, y1+1, x2, y2) + 1);
  }
  if (col_check(y2, x1, x2)) {
    ret = min(ret, get(x1, y1, x2, y2-1) + 1);
  }
  return (dp[y1][y2] = ret) + alpha;
}

int main(void)
{
  scanf("%lld%d%d", &k, &w, &h);
  for (int x = 1; x <= h; x++) {
    for (int y = 1; y <= w; y++) {
      ll tmp; scanf("%lld", &tmp);
      r_sum[x][y] = r_sum[x][y-1] + tmp;
      c_sum[y][x] = c_sum[y][x-1] + tmp;
    }
  }
  memset(dp, 0x3f, sizeof(dp));
  ll a = get(1, 1, h, w);
  transpose();
  memset(dp, 0x3f, sizeof(dp));
  ll b = get(1, 1, h, w);
  printf("%lld\n", min(a, b));
}
