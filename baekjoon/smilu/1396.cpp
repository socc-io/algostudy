#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct Query {
  int x, y;
  void input() { scanf("%d%d", &x, &y); }
} qs[100001];

struct Edge {
  int u, v, w;
  void input() { scanf("%d%d%d", &u, &v, &w); }
  bool operator<(const Edge &e) const { return w < e.w; }
} edges[100001];

struct UnionFind {
  int p[100001];
  int sz[100001];
  void clear() {
    for (int i = 0; i < 100001; i++) {
      p[i] = i;
      sz[i] = 1;
    }
  }
  int get(int u) { return p[u] == u ? u : (p[u] = get(p[u])); }
  bool merge(int a, int b) {
    a = get(a); b = get(b);
    if (a == b) return false;
    p[a] = b;
    sz[b] += sz[a];
    return true;
  }
  bool like(int a, int b) { return get(a) == get(b); }
  UnionFind() {
    clear();
  }
} uf;

int n, m, q;
int l[100001], r[100001], res[100001][2];
vector<int> ms[100001];

int main(void)
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) edges[i].input();
  scanf("%d", &q);
  for (int i = 0; i < q; i++) qs[i].input();

  sort(edges, edges + m);
  for (int i = 0; i < q; i++) l[i] = 0, r[i] = m;

  while (1) {
    for (int i = 0; i < 100001; i++) ms[i].clear();
    bool alive = false;
    for (int i = 0; i < q; i++) {
      if (l[i] == r[i]) continue;
      alive = true;
      int m = (l[i] + r[i]) >> 1;
      ms[m].push_back(i);
    }
    if (!alive) break;

    uf.clear();
    for (int i = 0; i < m; i++) {
      uf.merge(edges[i].u, edges[i].v);
      int w = edges[i].w;
      for (int j: ms[i]) {
        int x = uf.get(qs[j].x), y = uf.get(qs[j].y);
        if (x == y) {
          r[j] = i;
          res[j][0] = w;
          res[j][1] = uf.sz[x];
        } else {
          l[j] = i+1;
        }
      }
    }
  }
  for (int i = 0; i < q; i++) {
    if (l[i] == m) puts("-1");
    else printf("%d %d\n", res[i][0], res[i][1]);
  }
}
