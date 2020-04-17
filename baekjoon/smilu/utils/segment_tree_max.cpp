#include <cstring>
#include <algorithm>
using namespace std;

#define INF 0x7FFFFFFF
#define S_SIZE 500000
#define V_SIZE (4*S_SIZE)

struct MaxSegmentTree {
  int v[V_SIZE];
  MaxSegmentTree(int init = -INF) {
    for (int i = 0; i < V_SIZE; i++) v[i] = init;
  }
  void _update(int node, int begin, int end, int index, int value) {
    if (index < begin || index >= end) return;
    if (begin + 1 == end) {
      v[node] = value;
      return;
    }
    int mid = (begin + end) >> 1;
    _update(node<<1, begin, mid, index, value);
    _update((node<<1)+1, mid, end, index, value);
    v[node] = max(v[node<<1], v[(node<<1)+1]);
  }
  int _get(int node, int begin, int end, int from, int to) {
    if (end <= from || begin >= to) return -INF;
    if (from <= begin && end <= to) return v[node];
    int mid = (begin + end) >> 1;
    return max(
      _get(node<<1, begin, mid, from, to),
      _get((node<<1)+1, mid, end, from, to)
    );
  }
  int size = S_SIZE;
  void update(int index, int value) {
    // printf("update %d = %d\n", index, value);
    _update(1, 0, size, index, value);
  }
  int get(int from, int to) {
    // printf("get %d, %d\n", from, to);
    return _get(1, 0, size, from, to); 
  }
};