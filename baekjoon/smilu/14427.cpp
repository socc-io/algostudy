#include <cstdio>

int n, a[100000], m, v[300000];

int build(int u, int beg, int end) {
  if (end - beg == 1) return v[u] = beg;
  int l = u << 1, r = l + 1, mid = (beg + end) >> 1;
  int lv = build(l, beg, mid);
  int rv = build(r, mid, end);
  return v[u] = a[lv] <= a[rv] ? lv : rv;
}

int update(int u, int beg, int end, int pos) {
  if (pos < beg || pos >= end) return v[u];
  if (end - beg == 1) return v[u];
  int l = u << 1, r = l + 1, mid = (beg + end) >> 1;
  int lv = update(l, beg, mid, pos);
  int rv = update(r, mid, end, pos);
  return v[u] = a[lv] <= a[rv] ? lv : rv;
}

int main(void)
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++) scanf("%d", a+i);
  scanf("%d", &m);
  build(1, 0, n);
  for (int i = 0; i < m; i++) {
    int c; scanf("%d", &c);
    if (c == 1) {
      int pos, v; scanf("%d%d", &pos, &v);
      a[pos - 1] = v;
      update(1, 0, n, pos - 1);
    } else {
      printf("%d\n", v[1] + 1);
    }
  }
}
