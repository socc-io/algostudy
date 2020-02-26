#include <cstdio>
#include <vector>
using namespace std;

typedef pair<int,int> pii;

int n, m;
int tws[1000];
int kws[1000];

bool lock[1000];
int xy[1000];
int yx[1000];

bool available(int tw, int kw) {
  return (((tw + 1) / 2) <= kw && kw <= (tw * 3 / 4)) || (tw <= kw && kw <= (tw * 5 / 4));
}

void clear_lock() {
  for (int i = 0; i < 1000; i++) lock[i] = false;
}

bool dfs(int x) {
  if (lock[x]) return false;
  lock[x] = true;
  for (int i = 0; i < m; i++) {
    if (!available(tws[x], kws[i])) continue;
    if (yx[i] == -1 || dfs(yx[i])) {
      xy[x] = i;
      yx[i] = x;
      // printf("%d(%d) => %d(%d)\n", x, tws[x], i, kws[i]);
      return true;
    }
  }
  return false;
}

int main(void)
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) scanf("%d", &tws[i]);
  for (int i = 0; i < m; i++) scanf("%d", &kws[i]);
  for (int i = 0; i < n; i++) xy[i] = -1;
  for (int i = 0; i < m; i++) yx[i] = -1;

  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (xy[i] == -1) {
      clear_lock();
      ans += dfs(i);
    }
    else ++ans;
  }
  printf("%d", ans);
}
