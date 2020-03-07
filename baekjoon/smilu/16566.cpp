#include <cstdio>
#include <algorithm>
using namespace std;

int n, m, k;
int c[4000000];
int r[4000000];

int R(int i) {
  return r[i] == i ? i : (r[i] = R(r[i]));
}

int main(void)
{
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i < m; i++) scanf("%d", &c[i]);
  for (int i = 0; i < m; i++) r[i] = i;
  sort(c, c+m);
  for (int i = 0; i < k; i++) {
    int t; scanf("%d", &t);
    int v = upper_bound(c, c+m, t) - c;
    printf("%d\n", c[R(v)]);
    r[R(v)] = R(v) + 1;
  }
}
