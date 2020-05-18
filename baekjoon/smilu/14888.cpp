#include <bits/stdc++.h>
using namespace std;

int n;
int arr[11];
int n_add, n_sub, n_mul, n_div;
int mx, mm;

void dfs(int lev, int val) {
  if (lev == n) {
    mx = max(mx, val);
    mm = min(mm, val);
    return;
  }
  if (n_add) {
    --n_add;
    dfs(lev+1, val + arr[lev]);
    ++n_add;
  }
  if (n_sub) {
    --n_sub;
    dfs(lev+1, val - arr[lev]);
    ++n_sub;
  }
  if (n_mul) {
    --n_mul;
    dfs(lev+1, val * arr[lev]);
    ++n_mul;
  }
  if (n_div) {
    --n_div;
    dfs(lev+1, val / arr[lev]);
    ++n_div;
  }
}

int main(void)
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
  scanf("%d%d%d%d", &n_add, &n_sub, &n_mul, &n_div);
  mx = -0x7fffffff;
  mm = 0x7fffffff;
  dfs(1, arr[0]);
  printf("%d\n%d\n", mx, mm);
}
