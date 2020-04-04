#include <cstdio>
#include <vector>
using namespace std;

#define INF 0x7FFFFFFF

struct Node {
  struct Edge {
    Node *v;
    int c, r; // destination, capacity, reverse_index
    Edge(Node *v, int c, int r): v(v), c(c), r(r) {}
  };
  vector<Edge> edges;

  void add_edge(Node *v, int c) {
    edges.emplace_back(v, c, v->edges.size());
    v->edges.emplace_back(this, 0, edges.size() - 1);
  }

  bool dfs_lock;
  int dfs(Node* target, int mf) {
    if (this == target) return mf;
    
    if (dfs_lock) return 0;
    dfs_lock = true;

    for (Edge &e: edges) {
      if (e.c <= 0) continue;
      int f = e.v->dfs(target, min(e.c, mf));
      if (f <= 0) continue;
      e.c -= f;
      e.v->edges[e.r].c += f;

      dfs_lock = false;
      return f;
    }

    dfs_lock = false;
    return 0;
  }
};

#define NUM_LEFTS 200
#define NUM_RIGHTS 100
// source, sink, person[], food[]
#define NUM_NODE (2 + NUM_LEFTS + NUM_RIGHTS)
#define SOURCE 0
#define SINK   1
#define LEFTS  2
#define RIGHTS (2 + NUM_LEFTS)

Node nodes[NUM_NODE];
Node* lefts = nodes + LEFTS;
Node* rights = nodes + RIGHTS;
Node* source = nodes + SOURCE;
Node* sink = nodes + SINK;

int n, k, d;

int main(void)
{
  scanf("%d%d%d", &n, &k, &d);
  for (int i = 0; i < n; i++) {
    source->add_edge(&lefts[i], k);
  }
  for (int i = 0; i < d; i++) {
    int c; scanf("%d", &c);
    rights[i].add_edge(sink, c);
  }
  for (int i = 0; i < n; i++) {
    int z; scanf("%d", &z);
    for (int j = 0; j < z; j++) {
      int f; scanf("%d", &f); --f;
      lefts[i].add_edge(&rights[f], 1);
    }
  }

  int ans = 0;
  while(1) {
    int f = source->dfs(sink, INF);
    if (f == 0) break;
    ans += f;
  }
  printf("%d\n", ans);
}
