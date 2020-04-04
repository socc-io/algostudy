#include <cstdio>
#include <algorithm>
using namespace std;

bool in_range(int a, int b, int v) {
  return a < v && v < b;
}
bool cross(int a, int b, int p, int q) {
  if (a > b) swap (a, b);
  return in_range(a, b, p) != in_range(a, b, q);
}

int n;
int v[50][2];
bool c[50][50];
bool f[50];

int dfs(int u) {
  if (u >= n) return 0;

  int res = dfs(u + 1);

  bool valid = true;
  for (int i = 0; i < u; i++) {
    if (f[i] && c[i][u]) {
      valid = false;
      break;
    }
  }
  if (valid) {
    f[u] = true;
    res = max(res, dfs(u + 1) + 1);
    f[u] = false;
  }
  return res;
}

int main(void)
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &v[i][0], &v[i][1]);
  }
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (cross(v[i][0], v[i][1], v[j][0], v[j][1])) {
        c[i][j] = true;
        c[j][i] = true;
      }
    }
  }
  printf("%d\n", dfs(0));
}
