#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int n, k;

void solve() {
  scanf("%d%d", &n, &k);

  vector<int> arr(n);
  for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

  vector<int> cmp(arr);
  sort(cmp.begin(), cmp.end());
  cmp.erase(unique(cmp.begin(), cmp.end()), cmp.end());

  if (cmp.size() > k) { puts("-1"); return; }

  printf("%d\n", arr.size() * k);
  for (int i = 0; i < arr.size(); i++) {
    for (int j = 0; j < k; j++) {
      printf("%d ", cmp[j%cmp.size()]);
    }
  } puts("");
}

int main(void)
{
  int t; scanf("%d", &t);
  while (t--) solve();
}
