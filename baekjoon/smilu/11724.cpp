#include <cstdio>
#include <vector>
using namespace std;

int n, m;
vector<int> cn[1001];
int gids[1001];

void propagate_gid(int u, int gid) {
  if (gids[u] == gid) return;
  gids[u] = gid;
  for (auto it = cn[u].begin(); it != cn[u].end(); it++) {
    int v = *it;
    propagate_gid(v, gid);
  }
}

int main(void)
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    int u, v; scanf("%d%d", &u, &v);
    cn[u].push_back(v);
    cn[v].push_back(u);
  }

  int gid = 1;
  for (int i = 1; i <= n; i++) {
    if (gids[i] == 0) {
      propagate_gid(i, gid++);
    }
  }

  printf("%d", gid - 1);
}