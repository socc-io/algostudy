#include <cstdio>
#include <algorithm>
using namespace std;

int n;
int es[300001];

void solve()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++) scanf("%d", &es[i]);
  sort(es,es+n);

  int ret = 0;
  int begin = 0, end = es[0];
  for (int i = 0; i < n; i++) {
    if (i == end) {
      ++ret;
      begin = i;
      end = i + es[i];
    }
    end = max(end, begin + es[i]);
  }
  if (end == n) ++ret;

  printf("%d\n", ret);
}

int main(void)
{
  int t; scanf("%d", &t);
  while (t--) solve();
}
