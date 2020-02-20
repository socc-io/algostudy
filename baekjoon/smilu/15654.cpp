#include <cstdio>
#include <algorithm>
using namespace std;

int n, m;
int arr[8];
int v[8];
int vl = 0;
bool flag[8];

void select(int offset, int level) {
  if (level == m) {
    for (int i = 0; i < m; i++) printf("%d ", v[i]);
    puts("");
    return;
  }
  for (int i = 0; i < n; i++) {
    if (flag[i]) continue;
    v[vl++] = arr[i];
    flag[i] = true;
    select(i + 1, level + 1);
    --vl;
    flag[i] = false;
  }
}

int main(void)
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    scanf("%d", arr+i);
  }
  sort(arr, arr+n);
  select(0, 0);
}
