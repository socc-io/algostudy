#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

#define INF 0x7F000000
#define S_SIZE 500010
#define V_SIZE (4*S_SIZE)

struct market {
  int t; // time
  int x; // position
  int p; // profit
  market() {}
  market(int t, int x=0, int p=0): t(t), x(x), p(p) {}
  void input() { scanf("%d%d%d", &t, &x, &p); }
  bool operator<(const market &m) const {
    if (t != m.t) return t < m.t;
    return x < m.x;
  }
};

int n, up, down, home;
market ms[500010];

class MaxSegmentTree {
  int v[V_SIZE];
  void _update(int node, int begin, int end, int index, int value) {
    if (index < begin || index >= end) return;
    v[node] = max(v[node], value);
    if (begin + 1 == end) return;
    int mid = (begin + end) >> 1;
    _update(node<<1, begin, mid, index, value);
    _update((node<<1)+1, mid, end, index, value);
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
public:
  MaxSegmentTree(int init = -INF) {
    for (int i = 0; i < V_SIZE; i++) v[i] = init;
  }
  void update(int index, int value) {
    _update(1, 0, S_SIZE, index, value);
  }
  int get(int from, int to) {
    return _get(1, 0, S_SIZE, from, to);
  }
};

MaxSegmentTree st1, st2;

inline int get_profit(int x) {
  return max(
    st1.get(0, x) - x * down,
    st2.get(x, 500010) + x * up
  );
}

inline void update_profit(int x, int p) {
  st1.update(x, p + x * down);
  st2.update(x, p - x * up);
}

int main() {
  scanf("%d%d%d%d", &n, &up, &down, &home);
  for (int i = 0; i < n; i++) ms[i].input();
  sort(ms, ms+n);

  update_profit(home, 0);

  int begin = 0, end = 0;
  while (end < n) {
    while (ms[begin].t == ms[end].t && end < n) ++end;
    int size = end - begin;
    vector<int> dpr(size), dpl(size);
    dpr[0] = get_profit(ms[begin].x) + ms[begin].p;
    dpl[size-1] = get_profit(ms[end-1].x) + ms[end-1].p;
    for (int i = 1; i < size; i++) {
      dpr[i] = dpr[i-1] - (ms[begin+i].x - ms[begin+i-1].x) * down;
      dpr[i] = max(dpr[i], get_profit(ms[begin+i].x)) + ms[begin+i].p;
    }
    for (int i = size-2; i >= 0; i--) {
      dpl[i] = dpl[i+1] - (ms[begin+i+1].x - ms[begin+i].x) * up;
      dpl[i] = max(dpl[i], get_profit(ms[begin+i].x)) + ms[begin+i].p;
    }
    for (int i = 0; i < size; i++) {
      update_profit(ms[begin+i].x, max(dpr[i], dpl[i]));
    }
    begin = end;
  }

  int ans = get_profit(home);
  printf("%d\n", ans);
}
