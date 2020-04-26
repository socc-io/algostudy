#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define INF 0x7FFFFFFF

vector<pair<int,int>> adj[100001];
bool party[100001];
int n, m, k, q;
int d[100001], di[100001];
int l[100001], r[100001], res[100001];
vector<int> ms[100001];

struct UnionFind {
  int p[100001];
  void clear() {
    for (int i = 0; i < 100001; i++) {
      p[i] = i;
    }
  }
  int get(int u) { return p[u] == u ? u : (p[u] = get(p[u])); }
  bool merge(int a, int b) {
    a = get(a); b = get(b);
    if (a == b) return false;
    p[a] = b;
    return true;
  }
  bool like(int a, int b) { return get(a) == get(b); }
  UnionFind() {
    clear();
  }
} uf;

bool compare_d(int a, int b) { return d[a] > d[b]; }

struct Query {
  int x, y;
  void input() {
    scanf("%d%d", &x, &y);
    --x; --y;
  }
} qs[100001];

struct Edge {
  int u, v, w;
  void input() {
    scanf("%d%d%d", &u, &v, &w);
    --u; --v;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }
} edges[200001];

void dijkstra() {
  for (int i = 0; i < n; i++) d[i] = party[i] ? 0 : INF;
  priority_queue<pair<int,int>> q;
  vector<bool> visit(n, false);
  for (int i = 0; i < n; i++) if (party[i]) {
    q.push({0, i});
  }
  while (!q.empty()) {
    auto up = q.top(); q.pop();
    int ud = -up.first, u = up.second;
    if (visit[u]) continue;
    visit[u] = true;
    for (auto e: adj[u]) {
      int v = e.first, w = e.second;
      if (visit[v]) continue;
      int vd = ud + w;
      if (vd < d[v]) {
        d[v] = vd;
        q.push({-vd, v});
      }
    }
  }
}

int main(void)
{
  scanf("%d%d%d%d", &n, &m, &k, &q);
  for (int i = 0; i < m; i++) edges[i].input();
  for (int i = 0; i < k; i++) {
    int tmp; scanf("%d", &tmp);
    party[tmp-1] = true;
  }
  for (int i = 0; i < q; i++) qs[i].input();
  for (int i = 0; i < q; i++) l[i] = 0, r[i] = n;

  dijkstra();
  for (int i = 0; i < n; i++) di[i] = i;
  sort(di, di + n, compare_d);

  // printf("ds: "); for (int i = 0; i < n; i++) printf("%d ", d[i]); puts("");
  
  while (1) {
    for (int i = 0; i < n; i++) ms[i].clear();
    bool alive = false;
    for (int i = 0; i < q; i++) if (l[i] != r[i]) {
      alive = true;
      int m = (l[i] + r[i]) >> 1;
      ms[m].push_back(i);
    }
    if (!alive) break;
    uf.clear();
    for (int i = 0; i < n; i++) {
      int u = di[i];
      for (auto e: adj[u]) {
        int v = e.first;
        if (d[v] < d[u]) continue;
        uf.merge(u, v);
      }
      for (int j: ms[i]) {
        int x = uf.get(qs[j].x), y = uf.get(qs[j].y);
        if (x == y) {
          r[j] = i;
          res[j] = d[u];
        } else {
          l[j] = i+1;
        }
      }
    }
  }
  for (int i = 0; i < q; i++) {
    printf("%d\n", res[i]);
  }
}
