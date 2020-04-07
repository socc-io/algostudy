#include <cstdio>
#include <algorithm>
using namespace std;

#define INF 0x7FFFFFFF
#define MAX_C 4587520
#define BUCKET_SZ 16777216

int c, n, o;

class SegmentTree {
  int max_v[BUCKET_SZ];
  int min_v[BUCKET_SZ];
  int max_l[BUCKET_SZ];
  int min_l[BUCKET_SZ];
  void _update_lazy_min(int n_begin, int n_end, int index) {
    if (min_l[index] == 0) return;
    int n_size = n_end - n_begin;
    if (n_size >= 2) {
      min_l[index << 1] += min_l[index];
      min_l[(index << 1) + 1] += min_l[index];
    }
    min_v[index] += min_l[index];
    min_l[index] = 0;
  }
  void _update_lazy_max(int n_begin, int n_end, int index) {
    if (max_l[index] == 0) return;
    int n_size = n_end - n_begin;
    if (n_size >= 2) {
      max_l[index << 1] += max_l[index];
      max_l[(index << 1) + 1] += max_l[index];
    }
    max_v[index] += max_l[index];
    max_l[index] = 0;
  }
  void _update_min(int begin, int end, int v, int n_begin, int n_end, int index) {
    _update_lazy_min(n_begin, n_end, index);

    if (n_end <= begin || end <= n_begin) return; // 서로소
    if (begin <= n_begin && n_end <= end) { // 포함
      int n_size = n_end - n_begin;
      min_v[index] += v;
      if (n_size >= 2) {
        min_l[index << 1] += v;
        min_l[(index << 1) + 1] += v;
      }
      return;
    }
    int n_mid = (n_begin + n_end) >> 1;
    _update_min(begin, end, v, n_begin, n_mid, index << 1);
    _update_min(begin, end, v, n_mid, n_end, (index << 1) + 1);
    min_v[index] = min(min_v[index << 1], min_v[(index << 1) + 1]);
  }
  void _update_max(int begin, int end, int v, int n_begin, int n_end, int index) {
    _update_lazy_max(n_begin, n_end, index);

    if (n_end <= begin || end <= n_begin) return; // 서로소
    if (begin <= n_begin && n_end <= end) { // 포함
      int n_size = n_end - n_begin;
      max_v[index] += v;
      if (n_size >= 2) {
        max_l[index << 1] += v;
        max_l[(index << 1) + 1] += v;
      }
      return;
    }
    int n_mid = (n_begin + n_end) >> 1;
    _update_max(begin, end, v, n_begin, n_mid, index << 1);
    _update_max(begin, end, v, n_mid, n_end, (index << 1) + 1);
    max_v[index] = max(max_v[index << 1], max_v[(index << 1) + 1]);
  }
  int _get_min(int begin, int end, int n_begin, int n_end, int index) {
    _update_lazy_min(n_begin, n_end, index);
    
    if (n_end <= begin || end <= n_begin) return INF; // 서로소
    if (begin <= n_begin && n_end <= end) return min_v[index]; // 포함
    int n_mid = (n_begin + n_end) >> 1;
    return min(_get_min(begin, end, n_begin, n_mid, index << 1)
              ,_get_min(begin, end, n_mid, n_end, (index << 1) + 1));
  }
  int _get_max(int begin, int end, int n_begin, int n_end, int index) {
    _update_lazy_max(n_begin, n_end, index);
    
    if (n_end <= begin || end <= n_begin) return -INF; // 서로소
    if (begin <= n_begin && n_end <= end) return max_v[index]; // 포함
    int n_mid = (n_begin + n_end) >> 1;
    return max(_get_max(begin, end, n_begin, n_mid, index << 1)
              ,_get_max(begin, end, n_mid, n_end, (index << 1) + 1));
  }
public:
  int size = MAX_C;
  int v_max;
  int v_min;
  int update_range(int begin, int end, int v) {
    int r_max = _get_max(begin, end, 0, size, 1);
    int r_min = _get_min(begin, end, 0, size, 1);
    v = max(min(v, v_max - r_max), v_min - r_min);
    _update_max(begin, end, v, 0, size, 1);
    _update_min(begin, end, v, 0, size, 1);
    return v;
  }
  int get(int index) {
    return _get_max(index, index + 1, 0, size, 1);
  }
};

SegmentTree tree;

int main(void)
{
  char cmd[12];
  int p, q, r;
  scanf("%d%d%d", &c, &n, &o);

  tree.size = c;
  tree.v_max = n;
  tree.v_min = 0;

  for (int i = 0; i < o; i++) {
    scanf("%s", cmd);
    if (cmd[0] == 's') { // state
      scanf("%d", &p);
      printf("%d\n", tree.get(p));
    } else if (cmd[0] == 'g') { // group change
      scanf("%d%d%d", &p, &q, &r);
      printf("%d\n", tree.update_range(p, q+1, r));
    } else if (cmd[0] == 'c') { // change
      scanf("%d%d", &p, &q);
      printf("%d\n", tree.update_range(p, p+1, q));
    }
  }
}
