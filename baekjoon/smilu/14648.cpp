#include <cstdio>

typedef long long lld;

class SegmentTree {
  lld value[300020]; // over 2*2^{log2(x)} - 1
  lld lazy [300020];
  void _update_lazy(int n_begin, int n_end, int index) {
    if (lazy[index] == 0) return;
    int n_size = n_end - n_begin;
    if (n_size >= 2) {
      lazy[index << 1] += lazy[index];
      lazy[(index << 1) + 1] += lazy[index];
    }
    value[index] += lazy[index] * n_size;
    lazy[index] = 0;
  }
  void _add_range(int begin, int end, lld v, int n_begin, int n_end, int index) {
    #ifdef LOG_DFS
      printf("  _add(%d, %d, %d, %d, %d, %d)\n", begin, end, v, n_begin, n_end, index);
    #endif
    _update_lazy(n_begin, n_end, index);

    if (n_end <= begin || end <= n_begin) return; // 서로소
    if (begin <= n_begin && n_end <= end) { // 포함
      int n_size = n_end - n_begin;
      value[index] += v * n_size;
      if (n_size >= 2) {
        lazy[index << 1] += v;
        lazy[(index << 1) + 1] += v;
      }
      return;
    }
    int n_mid = (n_begin + n_end) >> 1;
    _add_range(begin, end, v, n_begin, n_mid, index << 1);
    _add_range(begin, end, v, n_mid, n_end, (index << 1) + 1);
    value[index] = value[index << 1] + value[(index << 1) + 1];
  }
  lld _get_range(int begin, int end, int n_begin, int n_end, int index) {
    #ifdef LOG_DFS
      printf("  _get(%d, %d, %d, %d, %d)\n", begin, end, n_begin, n_end, index);
    #endif
    _update_lazy(n_begin, n_end, index);
    
    if (n_end <= begin || end <= n_begin) return 0; // 서로소
    if (begin <= n_begin && n_end <= end) return value[index]; // 포함
    int n_mid = (n_begin + n_end) >> 1;
    return _get_range(begin, end, n_begin, n_mid, index << 1)
         + _get_range(begin, end, n_mid, n_end, (index << 1) + 1);
  }
public:
  int size = 100001;
  void add_range(int begin, int end, lld v) {
    #ifdef LOG_DFS
      printf("add(%d, %d, %d)\n", begin, end, v);
    #endif
    _add_range(begin, end, v, 0, size, 1);
  }
  lld get_range(int begin, int end) {
    #ifdef LOG_DFS
      printf("get(%d, %d)\n", begin, end);
    #endif
    return _get_range(begin, end, 0, size, 1);
  }
};

int n, q;
SegmentTree tree;

int main(void)
{
	scanf("%d%d", &n, &q);
	for (int i = 0; i < n; i++) {
		int tmp; scanf("%d", &tmp);
		tree.add_range(i, i+1, tmp);
	}
	for (int i = 0; i < q; i++) {
		int a, b, c, d, e;
		scanf("%d%d%d", &a, &b, &c);
		if (a == 1) {
			printf("%lld\n", tree.get_range(b-1, c));
			int left = tree.get_range(b-1, b);
			int right = tree.get_range(c-1, c);
			tree.add_range(b-1, b, right - left);
			tree.add_range(c-1, c, left - right);
		} else {
			scanf("%d%d", &d, &e);
			printf("%lld\n", tree.get_range(b-1, c) - tree.get_range(d-1, e));
		}
	}
}
