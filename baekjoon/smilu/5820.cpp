#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int,int> pii;

#define INF 0x7FFF0000
#define MAX_N 200001
#define MAX_K 1000001

struct Edge {
  int v;
  int w;
  Edge() {}
  Edge(int v, int w): v(v), w(w) {}
};

int N, K;
vector<Edge> edges[MAX_N];
int sz[MAX_N];
int cache[MAX_K];
vector<int> cache_f;
bool visit[MAX_N];

void init_size(int u, int p) {
  sz[u] = 1;
  for (auto e: edges[u]) {
    if (e.v == p || visit[e.v]) continue;
    init_size(e.v, u);
    sz[u] += sz[e.v];
  }
}

int dfs_get_centroid(int u, int p, int th) {
  for (auto e: edges[u]) {
    if (e.v == p || visit[e.v]) continue;
    if (sz[e.v] > th) return dfs_get_centroid(e.v, u, th);
  }
  return u;
}

int find_k(int u, int p, int udt, int lv) {
  int res = INF;
  if (udt > K) return INF;
  if (cache[K-udt] != INF) {
    res = min(res, cache[K-udt] + lv);
  }
  for (auto e: edges[u]) {
    if (e.v == p || visit[e.v]) continue;
    res = min(res, find_k(e.v, u, udt + e.w, lv + 1));
  }
  return res;
}

void update_cache(int u, int p, int udt, int lv) {
  if (udt > K) return;
  cache[udt] = min(cache[udt], lv);
  cache_f.push_back(udt);
  for (auto e: edges[u]) {
    if (e.v == p || visit[e.v]) continue;
    update_cache(e.v, u, udt + e.w, lv + 1);
  }
}

int go(int u) {
  init_size(u, -1);
  u = dfs_get_centroid(u, -1, sz[u] / 2);
  visit[u] = true;
  cache[0] = 0;
  int res = INF;

  for (int i: cache_f) cache[i] = INF;
  cache_f.clear();

  for (auto e: edges[u]) {
    if (visit[e.v]) continue;
    res = min(res, find_k(e.v, u, e.w, 1));
    update_cache(e.v, u, e.w, 1);
  }

  for (auto e: edges[u]) {
    if (visit[e.v]) continue;
    res = min(res, go(e.v));
  }
  return res;
}

int main(void)
{
  ios_base::sync_with_stdio(false); cin.tie(0);
  cin >> N >> K;
  for (int i = 1; i < N; i++) {
    int a, b, length;
    cin >> a >> b >> length;
    edges[a].emplace_back(b, length);
    edges[b].emplace_back(a, length);
  }
  fill(cache, cache+K+1, INF);
  int ans = go(0);
  cout << (ans == INF ? -1 : ans) << '\n';
}
