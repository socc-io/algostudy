#include <cstdio>
#include <vector>
#include <valarray>
#include <algorithm>
using namespace std;

typedef long long lld;

#define MAX_N 3001
#define MAX_V (4*MAX_N)
#define LL_INF 0x3f3f3f3f3f3f3f3f

struct Seg {
  lld l[MAX_V];
  lld r[MAX_V];
  lld lr[MAX_V];
  lld sm[MAX_V];
  int size;
  void _update(int node, int begin, int end, int index, lld value) {
    if (index < begin || index >= end) return;
    if (begin + 1 == end) {
      sm[node] += value;
      l[node]  += value;
      r[node]  += value;
      lr[node] += value;
      return;
    }
    int mid = (begin + end) >> 1, left = (node<<1), right = left+1;
    _update(left, begin, mid, index, value);
    _update(right, mid, end, index, value);
    sm[node] = sm[left] + sm[right];
    l[node] = max(l[left], sm[left] + l[right]);
    r[node] = max(r[right], sm[right] + r[left]);
    lr[node] = max({r[left]+l[right], lr[left], lr[right], sm[node]});
  }
  void update(int index, int value) {
    _update(1, 0, size, index, value);
  }
  void clear() {
    for (int i = 0; i < 4*size; i++) {
      l[i] = 0;
      r[i] = 0;
      lr[i] = 0;
      sm[i] = 0;
    }
  }
};

struct Mine {
  int x, y, w;
  void input() { scanf("%d%d%d", &x, &y, &w); }
  bool operator<(const Mine &m) const {
    if (x != m.x) return x < m.x;
    return y < m.y;
  }
};

int n;
Mine ms[MAX_N];
int zp[MAX_N];
Seg seg;

int main(void)
{
  scanf("%d", &n);
  seg.size = n;
  for (int i = 0; i < n; i++) ms[i].input();
  
  for (int i = 0; i < n; i++) zp[i] = ms[i].x;
  int *k = unique(zp, zp+n);
  sort(zp, k);
  for (int i = 0; i < n; i++) ms[i].x = lower_bound(zp, k, ms[i].x) - zp;

  for (int i = 0; i < n; i++) zp[i] = ms[i].y;
  k = unique(zp, zp+n);
  sort(zp, k);
  for (int i = 0; i < n; i++) ms[i].y = lower_bound(zp, k, ms[i].y) - zp;

  sort(ms, ms+n);

  lld ans = 0;
  for (int i = 0; i < n; i++) {
    if (i > 0 && ms[i-1].x == ms[i].x) continue;
    seg.clear();
    for (int j = i; j < n; j++) {
      seg.update(ms[j].y, ms[j].w);
      if (j == n-1 || ms[j].x != ms[j+1].x) {
        ans = max(ans, seg.lr[1]);
      }
    }
  }
  printf("%lld\n", ans);
}
