#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

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
  void set(int index, lld v) {
    lld diff = v - get(index);
    add_range(index, index + 1, diff);
  }
  void add_range(int begin, int end, lld v) {
    #ifdef LOG_DFS
      printf("add(%d, %d, %d)\n", begin, end, v);
    #endif
    _add_range(begin, end, v, 0, size, 1);
  }
  lld get(int index) { return get_range(index, index + 1); }
  lld get_range(int begin, int end) {
    #ifdef LOG_DFS
      printf("get(%d, %d)\n", begin, end);
    #endif
    return _get_range(begin, end, 0, size, 1);
  }
};
SegmentTree tree;

struct Query {
  int k, begin, end, index;
  lld ans;
  Query(int b, int c, int d, int _index) {
    k = b; begin = c; end = d; index = _index;
    ans = 0;
  }
};

int n, m;
vector<pair<int,int>> updates;
vector<Query*> queries;

bool by_k(const Query* a, const Query* b) {
  return a->k < b->k;
}
bool by_index(const Query* a, const Query* b) {
  return a->index < b->index;
}

int main(void)
{
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    int tmp; scanf("%d", &tmp);
    tree.add_range(i, i + 1, tmp);
  }
  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    int a, b, c, d;
    scanf("%d%d%d", &a, &b, &c);
    if (a == 1) {
      updates.push_back({b, c});
    } else {
      scanf("%d", &d);
      queries.push_back(new Query(b, c, d+1, i));
    }
  }
  sort(queries.begin(), queries.end(), by_k);

  int up = 0;
  for (auto query: queries) {
    while (up < query->k) {
      tree.set(updates[up].first, updates[up].second);
      up++;
    }
    query->ans = tree.get_range(query->begin, query->end);
  }
  sort(queries.begin(), queries.end(), by_index);
  for (auto query: queries) {
    printf("%lld\n", query->ans);
  }
}
