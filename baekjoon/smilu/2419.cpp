#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;

#define INF 0x7F000000

int n, m;
int np[301]; // negative x
int pp[301]; // positive x
int npn, ppn; // the number of positive, negative x

int cdp[2][301][301];

int dp(bool pos, int ni, int oi, int k) {
  // 양의 방향에서 ni개, 음의 방향에서 oi개 (pos == false 일 때는 정반대)
  // 먹은 상태에서 k개 더 먹었을 때 총 사라진 사탕수의 최소값
  // @arg pos: bool = ni is index of positive x
  // @arg ni: int = now index
  // @arg oi: int = opposite side(pos, neg) index
  if (k == 0) return 0;

  int &res = cdp[pos][ni][oi]; // cache reference
  if (res != -1) return res; // memoization
  res = INF;

  if (pos) { // If 수아 is now on positive side
    if (ni+1 < ppn) res = min(res, dp( pos, ni+1, oi, k-1) + k * (pp[ni+1] - pp[ni]));
    if (oi+1 < npn) res = min(res, dp(!pos, oi+1, ni, k-1) + k * (pp[ni] - np[oi+1]));
  } else {
    if (ni+1 < npn) res = min(res, dp( pos, ni+1, oi, k-1) - k * (np[ni+1] - np[ni]));
    if (oi+1 < ppn) res = min(res, dp(!pos, oi+1, ni, k-1) - k * (np[ni] - pp[oi+1]));
  }

  return res;
}

int main(void)
{
  scanf("%d%d", &n, &m);
  npn = 1; ppn = 1;
  for (int i = 0; i < n; i++) {
    int tmp; scanf("%d", &tmp);
    if (tmp < 0) np[npn++] = tmp;
    else         pp[ppn++] = tmp;
  }
  sort(np, np + npn, greater<int>());
  sort(pp, pp + ppn);

  int ans = 0;
  for (int i = 0; i <= n; i++) {
    // 사탕이 도중에 아예 사라지므로, 최적해에서 몇 개의 사탕을 먹을 수 있을지 모른다.
    // 때문에, 모두 시도해봄.
    memset(cdp, 0xFF, sizeof(cdp)); // Initialize with -1 (0xFFFFFFFF)
    ans = max(ans, i*m - dp(true, 0, 0, i));
  }

  printf("%d\n", ans);
}
