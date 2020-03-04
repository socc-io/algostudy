#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long lld;

#define INF 0x7FFFFFF0

struct Edge
{
  int cost;
  int v1;
  int v2;
  bool operator<(const Edge &b) const
  {
    if (cost != b.cost)
      return cost < b.cost;
    if (v1 != b.v1)
      return v1 < b.v1;
    return v2 < b.v2;
  }
};

int V, E;
Edge edges[200001];
vector<pair<int, int>> mst[50001];
int parent[50001];
int lca_parent[50001][22];
int lca_mc[50001][22][2];
int height[50001];
int in_mst[50001];
int mst_cnt;
int mst_cost;

int root(int index)
{
  if (parent[index] == index)
    return index;
  return parent[index] = root(parent[index]);
}
bool combine(int a, int b)
{
  if (root(a) == root(b))
    return false;
  parent[root(b)] = root(a);
  return true;
}
void make_tree(int u, int u_parent)
{
  for (auto uv_edge : mst[u])
  {
    int v = uv_edge.first;
    if (v == u_parent)
      continue;
    lca_parent[v][0] = u;
    lca_mc[v][0][0] = uv_edge.second;
    lca_mc[v][0][1] = -1;
    height[v] = height[u] + 1;
    for (int i = 1; i < 22; i++)
    {
      int mid = lca_parent[v][i - 1];
      lca_parent[v][i] = lca_parent[mid][i - 1];
      lca_mc[v][i][0] = max(lca_mc[v][i - 1][0], lca_mc[mid][i - 1][0]);
      lca_mc[v][i][1] = lca_mc[v][i-1][0] == lca_mc[mid][i-1][0]
        ? max(lca_mc[v][i-1][1], lca_mc[mid][i-1][1])
        : min(lca_mc[v][i-1][0], lca_mc[mid][i-1][0]);
    }
    make_tree(v, u);
  }
}
int max_cost_ai(int a, int i, int th)
{
  if (lca_mc[a][i][0] < th)
    return lca_mc[a][i][0];
  return lca_mc[a][i][1];
}
int max_cost_ab(int a, int b, int th)
{
  if (height[a] > height[b])
    swap(a, b);
  int ret = -1;
  for (int i = 21; i >= 0; i--)
  {
    if (height[b] - (1 << i) < height[a])
      continue;
    ret = max(ret, max_cost_ai(b, i, th));
    b = lca_parent[b][i];
  }
  if (a == b)
    return ret;
  for (int i = 21; i >= 0; i--)
  {
    if (lca_parent[a][i] == lca_parent[b][i])
      continue;
    ret = max(ret, max_cost_ai(a, i, th));
    ret = max(ret, max_cost_ai(b, i, th));
    a = lca_parent[a][i];
    b = lca_parent[b][i];
  }
  ret = max(ret, max_cost_ai(a, 0, th));
  ret = max(ret, max_cost_ai(b, 0, th));
  return ret;
}

int main(void)
{
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);

  cin >> V >> E;
  for (int i = 0; i < E; i++)
  {
    cin >> edges[i].v1 >> edges[i].v2 >> edges[i].cost;
  }
  sort(edges, edges + E);

  for (int i = 0; i <= V; i++)
    parent[i] = i;
  for (int i = 0; i < E; i++)
  {
    int v1 = edges[i].v1;
    int v2 = edges[i].v2;
    int cost = edges[i].cost;
    if (combine(v1, v2))
    {
      mst_cost += cost;
      in_mst[i] = true;
      mst[v1].push_back(make_pair(v2, cost));
      mst[v2].push_back(make_pair(v1, cost));
      mst_cnt++;
    }
    if (mst_cnt == V - 1)
      break;
  }
  if (mst_cnt != V - 1 || E <= V - 1)
  {
    puts("-1");
    return 0;
  }
  make_tree(1, 0);
  lld ans = 1e11;
  for (int i = 0; i < E; i++)
  {
    int v1 = edges[i].v1;
    int v2 = edges[i].v2;
    int cost = edges[i].cost;

    if (in_mst[i])
      continue;
    int mc = max_cost_ab(v1, v2, cost);
    if (mc == -1)
      continue;
    ans = min(ans, (lld)(mst_cost - mc + cost));
  }
  if (ans == 1e11 || ans == mst_cost)
    ans = -1;
  printf("%lld\n", ans);
}