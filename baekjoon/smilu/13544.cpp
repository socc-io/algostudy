#include <cstdio>
#include <algorithm>
using namespace std;

int buf[2000000];
int buf_off;

int* v[300000];
int a[100000];

void build(int idx, int begin, int end) {
  int size = end - begin;
  v[idx] = buf + buf_off; buf_off += size;
  for (int i = 0; i < size; i++) v[idx][i] = a[begin + i];
  sort(v[idx], v[idx] + size);
  if (size == 1) return;
  int mid = (begin + end) / 2;
  build(idx*2  , begin, mid);
  build(idx*2+1, mid  , end);
}

int query(int idx, int begin, int end, int from, int to, int k) {
  if (end <= from || to <= begin) return 0;
  if (from <= begin && end <= to) {
    int *vs = v[idx], size = end - begin;
    return vs + size - upper_bound(vs, vs + size, k);
  }
  int mid = (begin + end) / 2;
  return query(idx*2  , begin, mid, from, to, k) +
         query(idx*2+1, mid  , end, from, to, k);
}

int main(void)
{
  int l, r, k, n, m, pa = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
  build(1, 0, n);
  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    scanf("%d%d%d", &l, &r, &k);
    l ^= pa; r ^= pa; k ^= pa;
    printf("%d\n", pa = query(1, 0, n, l-1, r, k));
  }
}
