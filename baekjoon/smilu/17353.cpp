#include <cstdio>

typedef long long lld;

int n, q;
lld a[100000], lazy[400000][2];

// void build(int node, int begin, int end) {
//   int size = end - begin;
//   if (size >= 2) {
//     int mid = (begin + end) / 2;
//     build(node*2  , begin, mid);
//     build(node*2+1, mid  , end);
//   } else if (size == 1) {
//     scanf("%d", &a[begin]);
//   }
// }

void update_lazy(int node, int begin, int end) {
  // printf("update_lazy(%d, %d, %d)\n", node, begin, end);
  if (lazy[node][0] == 0 && lazy[node][1] == 0) return;
  int size = end - begin;
  if (size == 1) {
    a[begin] += lazy[node][0];
  } else {
    int mid = (begin + end) / 2;
    lazy[node*2  ][0] += lazy[node][0];
    lazy[node*2  ][1] += lazy[node][1];
    lazy[node*2+1][0] += lazy[node][0] + (mid - begin) * lazy[node][1];
    lazy[node*2+1][1] += lazy[node][1];
  }
  lazy[node][0] = 0;
  lazy[node][1] = 0;
}

void update_lazy_to(int node, int begin, int end, int index) {
  // printf("update_lazy_to(%d, %d, %d, %d)\n", node, begin, end, index);
  if (index < begin || index >= end) return;
  int size = end - begin;
  int mid = (begin + end) / 2;
  update_lazy(node, begin, end);
  if (size == 1) return;
  update_lazy_to(node*2  , begin, mid, index);
  update_lazy_to(node*2+1, mid,   end, index);
}

lld add_value;
void _add(int node, int begin, int end, int from, int to) {
  // printf("_add(%d, %d, %d, %d, %d, %d)\n", node, begin, end, from, to, value);
  if (to <= begin || end <= from) return;
  int mid = (begin + end) / 2;
  if (from <= begin && end <= to) {
    lazy[node][0] += add_value;
    lazy[node][1] += 1;
    add_value += end - begin;
    return;
  }
  _add(node*2  , begin, mid, from, to);
  _add(node*2+1, mid  , end, from, to);
}

void add(int l, int r) {
  add_value = 1;
  _add(1, 0, n, l-1, r);
}

lld get(int index) {
  update_lazy_to(1, 0, n, index - 1);
  return a[index - 1];
}

int main(void)
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
  scanf("%d", &q);
  for (int i = 0; i < q; i++) {
    int cmd, r1, r2; scanf("%d%d", &cmd, &r1);
    if (cmd == 1) {
      scanf("%d", &r2);
      add(r1, r2);
    } else {
      printf("%lld\n", get(r1));
    }
  }
}
