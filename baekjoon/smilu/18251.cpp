#include <cstdio>
#include <algorithm>
using namespace std;

#define INF 0x7FFFFFFF
#define NUM 262143

typedef long long lld;

int n;
int x[NUM], w[NUM], idx[NUM], xii;

void set_children_position(int u, int xv) {
  if (u*2 <= n) set_children_position(u*2, xv+1);
  idx[u] = xii;
  x[xii++] = xv;
  if (u*2+1 <= n) set_children_position(u*2+1, xv+1);
}

int main(void)
{
  lld ans = -INF;
  scanf("%d", &n);
  set_children_position(1, 0);
  for (int i = 1; i <= n; i++) scanf("%d", &w[idx[i]]);
  for (int i = 0; i < n; i++) ans = max(ans, (lld)w[i]);
  if (ans <= 0) { printf("%lld\n", ans); return 0; }
  for(int i = 0; i < 20; i++) {
    for(int j = i; j < 20; j++) {
      lld now = 0, mx = 0;
      for(int k=0; k<n; k++){
        if(x[k] < i || x[k] > j) continue;
        now = max(0LL, now + w[k]);
        mx = max(mx, now);
      }
      ans = max(ans, mx);
    }
  }
  printf("%lld\n", ans);
}
