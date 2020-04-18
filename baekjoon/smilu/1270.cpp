#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long lld;

lld n;
lld arr[100000];

void solve()
{
  scanf("%lld", &n);
  for (lld i = 0; i < n; i++) scanf("%lld", &arr[i]);
  sort(arr, arr+n);

  lld th = n / 2;
  lld ans = -1, val = 0x7FFFFFFFFFFF, cnt = -1;
  for (lld i = 0; i < n; i++) {
    if (arr[i] != val) {
      if (cnt > th) {
        ans = val;
        break;
      }
      val = arr[i];
      cnt = 1;
    } else {
      ++cnt;
    }
  }
  if (cnt > th) ans = val;

  if (ans == -1) puts("SYJKGW");
  else printf("%lld\n", ans);
}

int main(void)
{
  int t; scanf("%d", &t);
  while (t--) solve();
}
