#include <cstring>
#include <algorithm>
using namespace std;

#define INF 0x7FFFFFFF
#define S_SIZE 500000
#define V_SIZE (4*S_SIZE)

class MaxSegmentTree {
  int v[V_SIZE];
  MaxSegmentTree(int init = -INF) {
    for (int i = 0; i < V_SIZE; i++) v[i] = init;
  }
  void update(int node, int begin, int end, int index, int value) {
    if (index < begin || index >= end) return;
    v[node] = max(v[node], value);
    if (begin + 1 == end) return;
    int mid = (begin + end) >> 1;
    update(node<<1, begin, mid, index, value);
    update((node<<1)+1, mid, end, index, value);
  }
  int get(int node, int begin, int end, int from, int to) {
    if (end <= from || begin >= to) return -INF;
    if (from <= begin && end <= to) return v[node];
    int mid = (begin + end) >> 1;
    return max(
      get(node<<1, begin, mid, from, to),
      get((node<<1)+1, mid, end, from, to)
    );
  }
};
