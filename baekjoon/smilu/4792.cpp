#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

struct UnionFind {
  int p[1010];
  void clear() {
    for (int i = 0; i < 1010; i++) p[i] = i;
  }
  int getpar(int u) {
    if (p[u] == u) return u;
    return p[u] = getpar(p[u]);
  }
  bool merge(int a, int b) {
    a = getpar(a); b = getpar(b);
    if (a == b) return false;
    p[a] = b;
    return true;
  }
} uf;

struct Edge {
  int u, v, blue;
  void input() {
    char s[3];
    scanf("%s%d%d", s, &u, &v);
    blue = s[0] == 'B';
  }
};

vector<Edge> edges;

bool compare_r(const Edge &a, const Edge &b) { return a.blue > b.blue; }
bool compare_b(const Edge &a, const Edge &b) { return a.blue < b.blue; }

int n, m, k;

int mst() {
  int res = 0, cnt = 0;
  uf.clear();
  for (int i = 0; i < m; i++) {
    const Edge &e = edges[i];
    if (uf.merge(e.u, e.v)) {
      res += e.blue;
      if (++cnt >= n-1) break;
    }
  }
  return res;
}

void solve() {
  edges.resize(m);
  for (int i = 0; i < m; i++) edges[i].input();
  sort(edges.begin(), edges.end(), compare_r);
  if(k > mst()) { puts("0"); return; }
  sort(edges.begin(), edges.end(), compare_b);
  printf("%d\n", k >= mst());
}

int main(void)
{
  while (1) {
    scanf("%d%d%d", &n, &m, &k);
    if (n == 0 && m == 0 && k == 0) break;
    solve();
  }
}
