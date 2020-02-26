#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int n;
int a[1000000];
int lis[1000000];
int pos[1000000];
int last;

int main(void)
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  lis[0] = a[0];
  for (int i = 1; i < n; i++) {
    int * lo = lower_bound(lis, lis + last + 1, a[i]);
    *lo = a[i];
    pos[i]  = lo - lis;
    if (lo == lis + last + 1) ++last;
  }
  printf("%d\n", last + 1);
  vector<int> ans;
  int target = last;
  for (int i = n - 1; i >= 0; i--) {
    if (pos[i] != target) continue;
    ans.push_back(a[i]);
    --target;
  }
  reverse(ans.begin(), ans.end());
  for (int i = 0; i < ans.size(); i++) {
    printf("%d ", ans[i]);
  }
}