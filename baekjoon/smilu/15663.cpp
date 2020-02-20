#include <cstdio>
#include <algorithm>
using namespace std;

int n, m;
int arr[8];
int v[8];
int vl = 0;
bool f[8];

void select(int level) {
  if (level == m) {
    for (int i = 0; i < m; i++) printf("%d ", v[i]);
    puts("");
    return;
  }
  int prev = -1;
  for (int i = 0; i < n; i++) {
    if (f[i]) continue;
    if (arr[i] == prev) continue;
    prev = arr[i];
    v[vl++] = arr[i];
    f[i] = true;
    select(level + 1);
    --vl;
    f[i] = false;
  }
}

int main(void)
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    scanf("%d", arr+i);
  }
  sort(arr, arr+n);
  select(0);
}
