#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;
int par[100001];
int lazy[100001];
int budget[100001];
vector<int> chrn[100001];

void earn(int pi, int amount) {
  budget[pi] += amount;
  lazy[pi] += amount;
}

void update_lazy(int pi) {
  if (lazy[pi] == 0) return;
  for (auto ci: chrn[pi]) {
    earn(ci, lazy[pi]);
  }
  lazy[pi] = 0;
}

int get_budget(int pi) {
  vector<int> ps;
  int cur = pi;
  while (par[cur] != -1) {
    cur = par[cur];
    ps.push_back(cur);
  }
  reverse(ps.begin(), ps.end());
  for (auto u: ps) update_lazy(u);
  return budget[pi];
}

int main(void)
{
  scanf("%d%d", &N, &M);
  for (int i = 1; i <= N; i++) {
    scanf("%d", &par[i]);
    chrn[par[i]].push_back(i);
  }
  for (int i = 0; i < M; i++) {
    int cmd, pi; scanf("%d%d", &cmd, &pi);
    if (cmd == 1) {
      int amount; scanf("%d", &amount);
      earn(pi, amount);
    } else {
      printf("%d\n", get_budget(pi));
    }
  }
}
