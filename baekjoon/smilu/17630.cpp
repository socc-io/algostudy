#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

const ll LL_INF = 0x7fffffffffffffff;

struct edge {
  ll v, w;
  edge(ll v=0, ll w=0):v(v),w(w) {}
};

int n, m, s, e;
vector<edge> adj[2001];
int k;
int path[2001];
bool in_path[2001];
int lca[2001];
ll opt[2001];

void set_lca_dfs(const vector<vector<int>> &chd, int u, int ca) {
  if (lca[u]) return;
  lca[u] = ca;
  for (int v: chd[u]) {
    set_lca_dfs(chd, v, ca);
  }
}

void set_lca(const vector<vector<int>> &chd, const vector<int> &par, int src, int dst) {
  int cur = dst;
  int ca = k-1;
  while (cur != src) {
    set_lca_dfs(chd, cur, ca--);
    in_path[cur] = true;
    cur = par[cur];
  }
  set_lca_dfs(chd, cur, ca--);
  in_path[cur] = true;
}

vector<vector<int>> build_tree(const vector<int> &par) {
  vector<vector<int>> chd(n+1); // children
  for (int i = 1; i <= n; i++) {
    int p = par[i];
    if (p == i || p == 0) continue;
    chd[p].push_back(i);
  }
  return chd;
}

pair<vector<ll>,vector<int>> dijkstra(int src) {
  priority_queue<pii> q;
  vector<ll> dist(n+1, LL_INF);
  vector<int> par(n+1, 0);
  vector<bool> visit(n+1, false);
  dist[src] = 0;
  par[src] = src;
  q.push({0, src});
  while(!q.empty()) {
    auto t = q.top(); q.pop();
    int u = t.second;
    ll ud = t.first;
    if (visit[u]) continue;
    visit[u] = true;
    for (auto e: adj[u]) {
      ll w = e.w, v = e.v, vd = w-ud;
      if (vd < dist[v]) {
        dist[v] = vd;
        par[v] = u;
        q.push({-vd, v});
      }
    }
  }
  return {dist, par};
}

int main(void)
{
  scanf("%d%d%d%d", &n, &m, &s, &e);
  for (int i = 0; i < m; i++) {
    int a, b, w; scanf("%d%d%d", &a, &b, &w);
    adj[a].push_back(edge(b, w));
    adj[b].push_back(edge(a, w));
  }
  scanf("%d", &k);
  for (int i = 0; i < k; i++) scanf("%d", &path[i]);

  auto src_dijkstra = dijkstra(s);
  auto src_dist = src_dijkstra.first;
  // printf("src dist: "); for (int i = 1; i <= n; i++) printf("%d ", src_dist[i]); puts("");
  auto src_par = src_dijkstra.second;
  for (int i = 1; i < k; i++) src_par[path[i]] = path[i-1];
  auto chd = build_tree(src_par);
  set_lca(chd, src_par, s, e);

  auto dst_dijkstra = dijkstra(e);
  auto dst_dist = dst_dijkstra.first;
  // printf("dst dist: "); for (int i = 1; i <= n; i++) printf("%d ", dst_dist[i]); puts("");

  for (int i = 0; i < k; i++) opt[i] = LL_INF;

  for (int u = 1; u <= n; u++) {
    for (auto e: adj[u]) {
      ll v = e.v, w = e.w;
      if (in_path[u] && in_path[v] && abs(lca[u]-lca[v]) == 1) continue;
      // printf("(%d, %d, %d)\n", u, v, w);
      ll d = src_dist[u] + w + dst_dist[v];
      ll f = lca[u], t = lca[v];
      for (int i = f; i < t; i++) {
        opt[i] = min(opt[i], d);
      }
    }
  }

  for (int i = 0; i < k-1; i++) printf("%lld\n", opt[i] == LL_INF ? -1 : opt[i]);
}
