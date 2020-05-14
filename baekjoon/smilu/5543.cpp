#include <cstdio>
#include <algorithm>
using namespace std;
int min(int *a, int n) {
  int v = a[0];
  for (int i = 1; i < n; i++) v = min(v, a[i]);
  return v;
}
int main(void)
{
  int c[5]; for (int i = 0; i < 5; i++) scanf("%d", c+i);
  printf("%d\n", min(c,3)+min(c+3,2)-50);
}
