#include <cstdio>
#include <vector>
using namespace std;

#define MAXN 100000

int n;
int chs[MAXN];
bool tin[MAXN];
int visit[MAXN];

void apply_tin(int root) {
  int cur = root;
  while(1) {
    tin[cur] = true;
    cur = chs[cur];
    if (cur == root) break;
  }
}

int find_team(int root, int id) {
  int cur = root;
  while(1) {
    if (visit[cur] == id) {
      return cur;
    } else if (visit[cur]) {
      return -1;
    }
    visit[cur] = id;
    cur = chs[cur];
  }
}

void solve()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int tmp; scanf("%d", &tmp); --tmp;
    chs[i] = tmp;
    tin[i] = false;
    visit[i] = false;
  }
  int id = 1;
  for (int i = 0; i < n; i++) {
    if (visit[i]) continue;
    int root = find_team(i, id++);
    if (root != -1) apply_tin(root);
  }
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    if (!tin[i]) cnt++;
  }
  printf("%d\n", cnt);
}

int main(void)
{
  int t;
  scanf("%d", &t);
  while(t--) solve();
}