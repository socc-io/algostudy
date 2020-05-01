#include <cstdio>
#include <vector>
using namespace std;

struct Boo {
  int a, b, c;
};

int n, m;
vector<int> adj[100001];
bool visit[100001];
bool finished[100001];
vector<Boo> boos;

bool dfs(int u, int p) {
  // printf("%d, %d\n", u, p);
  vector<int> chd;
  visit[u] = true;
  for (int v: adj[u]) {
    if (v == p) continue;
    if (visit[v]) {
      if (!finished[v]) {
        chd.push_back(v);
      }
    }
    else if (!dfs(v, u)) chd.push_back(v);
  }
  finished[u] = true;
  for (int i = 1; i < chd.size(); i += 2) {
    boos.push_back({chd[i-1],u,chd[i]});
  }
  if ((chd.size() & 1) && p) {
    boos.push_back({chd.back(),u,p});
    return true;
  }
  return false;
}

int main(void)
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    int u, v; scanf("%d%d", &u, &v);
    adj[u].emplace_back(v);
    adj[v].emplace_back(u);
  }
  for (int i = 1; i <= n; i++) if (!visit[i]) {
    dfs(i, 0);
  }
  printf("%lu\n", boos.size());
  for (auto &b: boos) {
    printf("%d %d %d\n", b.a, b.b, b.c);
  }
}
