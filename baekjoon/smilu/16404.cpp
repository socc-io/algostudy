#include <cstdio>
#include <vector>
using namespace std;

// #define LOG_DFS

typedef long long lld;

class SegmentTree {
  lld value[300020];
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

int n, m;
vector<int> children[100001];
int begins[100001];
int ends  [100001];

SegmentTree tree;

int assign_number(int index, int number) {
  begins[index] = number;
  int last = number + 1;
  for (int child: children[index]) {
    last = assign_number(child, last);
  }
  ends[index] = last;
  return last;
}

int main(void)
{
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    int parent;
    scanf("%d", &parent);
    if (parent != -1) {
      children[parent].push_back(i);
    }
  }
  int last = assign_number(1, 1);
  tree.size = last + 1;
  for (int i = 0; i < m; i++) {
    int command, index;
    scanf("%d%d", &command, &index);
    if (command == 1) {
      lld weight;
      scanf("%lld", &weight);
      tree.add_range(begins[index], ends[index], weight);
    } else {
      printf("%lld\n", tree.get_range(begins[index], begins[index] + 1));
    }
  }
}
