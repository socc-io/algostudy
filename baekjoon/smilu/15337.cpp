#include <cstdio>
#include <algorithm>
using namespace std;

struct evt {
  int t;
  int pi;
  int up;
  evt() {}
  evt(int t, int pi, int up): t(t), pi(pi), up(up) {}
  bool operator<(const evt &o) const {
    if (t == o.t) return up < o.up;
    return t < o.t;
  }
} es[400000];

int n, en;
int stack[200000];

int main(void)
{
  scanf("%d", &n); en = n<<1;
  for (int i = 0; i < n; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    es[i<<1] = evt(a, i, 1);
    es[(i<<1)|1] = evt(b, i, -1);
  }
  sort(es, es+en);

  int cnt = 0, max_cnt = 0, g_up_cnt = 0, g_down_cnt = 0;
  for (int i = 0;;) {
    int up_cnt = 0;
    int down_cnt = 0;
    int batch_begin = i;
    int batch_time = es[i].t;
    for (;es[i].t == batch_time && i < en; i++) {
      cnt += es[i].up;
      max_cnt = max(max_cnt, cnt);
      if (es[i].up > 0) ++up_cnt;
      else              ++down_cnt;
    }
    for (int j = batch_begin; j < i; j++) {
      if (es[j].up > 0) stack[es[j].pi] -= g_down_cnt + down_cnt;
      else              stack[es[j].pi] += g_up_cnt;
    }
    g_up_cnt   += up_cnt;
    g_down_cnt += down_cnt;
    if (i >= en) break;
  }

  printf("%d\n%d\n", *max_element(stack, stack+n), max_cnt);
}
