#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_N 100010

vector<int> adj[MAX_N];
int par[MAX_N][25];
int level[MAX_N];

void make_tree(int u, int p) {
  level[u] = level[p] + 1;
  par[u][0] = p;
  for (int i = 1; i < 25; i++)
    par[u][i] = par[par[u][i-1]][i-1];
  for (int v: adj[u])
    if (v != p) make_tree(v, u);
}

int ancestor(int p, int l) {
  for (int i = 24; i >= 0; i--)
    if (level[par[p][i]] >= l) p = par[p][i];
  return p;
}

int lca(int p, int q) {
  if (level[p] != level[q]) {
    if (level[p] < level[q]) swap(p, q);
    p = ancestor(p, level[q]);
  }
  if (p == q) return p;
  for (int i = 24; i >= 0; i--) {
    int pa = par[p][i], qa = par[q][i];
    if (pa == qa) continue;
    p = pa; q = qa;
  }
  return par[p][0];
}

int get_dist(int p, int q) {
  int ca = lca(p, q);
  return level[p] + level[q] - (level[ca] << 1);
}

int get_mid(int p, int q) {
  int dist = get_dist(p, q);
  if (dist & 1) return 0;
  if (level[p] < level[q]) swap(p, q);
  return ancestor(p, level[p] - (dist >> 1));
}

int main(void)
{
  int n, q;
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  make_tree(1, 0);
  
  scanf("%d", &q);
  for (int i = 0; i < q; i++) {
    int a, b, c, m;
    scanf("%d%d%d", &a, &b, &c);

    vector<int> ms;
    if ((m = get_mid(a, b))) ms.push_back(m);
    if ((m = get_mid(b, c))) ms.push_back(m);
    if ((m = get_mid(a, c))) ms.push_back(m);

    int res = 0;
    for (int im: ms) {
      int da = get_dist(im, a);
      int db = get_dist(im, b);
      int dc = get_dist(im, c);
      if (da == db && db == dc) {
        res = im;
        break;
      }
    }
    printf("%d\n", res ? res : -1);
  }
}
