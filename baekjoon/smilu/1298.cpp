#include <cstdio>
#include <vector>
using namespace std;

typedef vector<int> vi;

int n, m;
vi nt[100];
int nc[100];
int mc[100];
bool lock[100];

bool dfs(int u) {
  if (lock[u]) return false;
  lock[u] = true;
  for (int i = 0; i < nt[u].size(); i++) {
    int l = nt[u][i];
    if (mc[l] == n || dfs(mc[l])) {
      nc[u] = l;
      mc[l] = u;
      return true;
    }
  }
  return false;
}

int main(void)
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    int u, l;
    scanf("%d%d", &u, &l);
    --u; --l;
    nt[u].push_back(l);
  }

  for (int i = 0; i < n; i++) {
    nc[i] = n;
    mc[i] = n;
  }

  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (nc[i] == n) {
      for (int j = 0; j < n; j++) {
        lock[j] = false;
      }
      ans += dfs(i);
    } else ++ans;
  }
  printf("%d", ans);
}