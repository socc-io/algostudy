#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

#define MAX_N 502
#define INF 0x7F000000

int n;
int sink;
int f[MAX_N][MAX_N];
int level[MAX_N];
int c[MAX_N];

bool find_level() {
  memset(level, 0xFF, sizeof(level));
  level[0] = 0;
  queue<int> q;
  q.push(0);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int v = 0; v <= sink; v++) {
      if (!f[u][v]) continue;
      if (level[v] != -1) continue;
      level[v] = level[u] + 1;
      q.push(v);
    }
  }
  return level[sink] != -1;
}

int make_flow(int u, int mf) {
  if (u == sink) return mf;
  for (int &v = c[u]; v <= sink; v++) {
    if (!f[u][v]) continue;
    if (level[v] <= level[u]) continue;
    int res = make_flow(v, min(mf, f[u][v]));
    if (res) {
      f[u][v] -= res;
      f[v][u] += res;
      return res;
    }
  }
  return 0;
}

int main(void)
{
  int ans = 0;
  scanf("%d", &n);
  sink = n+1;
  for (int i = 1; i <= n; i++) {
    int side; scanf("%d", &side);
    if (side == 1) f[0][i] = INF;
    else if (side == 2) f[i][sink] = INF;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++ ) {
      scanf("%d", &f[i][j]);
    }
  }
  while (find_level()) {
    memset(c, 0x00, sizeof(c));
    while (1) {
      int res = make_flow(0, INF);
      if (res == 0) break;
      ans += res;
    }
  }
  printf("%d\n", ans);
  for (int i = 1; i <= n; i++) {
    if (level[i] != -1) printf("%d ", i);
  } puts("");
  for (int i = 1; i <= n; i++) {
    if (level[i] == -1) printf("%d ", i);
  } puts("");
}
