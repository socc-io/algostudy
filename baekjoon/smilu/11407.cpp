#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef pair<int,int> pii;

#define INF 0x7FFFFFF0

int n, m;
int r[202][202];
int c[202][202];

vector<int> find_path(int src, int dst) {
  vector<int> bt(202, -1);
  vector<int> dist(202, INF);
  vector<bool> inq(202, false);
  queue<int> q;
  q.push(src);
  bt[src] = src;
  dist[src] = 0;
  inq[src] = true;
  bool found = false;
  while(!q.empty()) {
    int u = q.front();
    q.pop();
    inq[u] = false;
    for (int i = 0; i < 202; i++) {
      if (r[u][i] <= 0) continue;
      int v_dist = dist[u] + c[u][i];
      if (v_dist < dist[i]) {
        dist[i] = v_dist;
        bt[i] = u;
        if (!inq[i]) {
          q.push(i);
          inq[i] = true;
        }
      }
    }
    if (found) break;
  }

  vector<int> ans;
  if (bt[dst] == -1) return ans;
  int cur = dst;
  while (bt[cur] != cur) {
    ans.push_back(cur);
    cur = bt[cur];
  }
  ans.push_back(cur);
  reverse(ans.begin(), ans.end());
  return ans;
}

int get_min_flow(vector<int> path) {
  int min_flow = r[path[0]][path[1]];
  for (int i = 2; i < path.size(); i++) {
    int flow = r[path[i-1]][path[i]];
    if (flow < min_flow) min_flow = flow;
  }
  return min_flow;
}

void make_flow(vector<int> path) {
  int min_flow = get_min_flow(path);
  for (int i = 1; i < path.size(); i++) {
    int u = path[i-1], v = path[i];
    r[u][v] -= min_flow;
    r[v][u] += min_flow;
  }
}

int main(void)
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) scanf("%d", &r[0][2+i]);
  for (int i = 0; i < m; i++) scanf("%d", &r[2+n+i][1]);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &r[2+j][2+n+i]);
    }
  }
  for (int i = 0; i < m; i++) {
    int u = 2+n+i;
    for (int j = 0; j < n; j++) {
      int v = 2+j;
      scanf("%d", &c[v][u]);
      c[u][v] = -c[v][u];
    }
  }
  while(1) {
    vector<int> path = find_path(0, 1);
    if (path.size() == 0) break;
    make_flow(path);
  }
  int sum_cost = 0;
  int sum_sell = 0;
  for (int i = 0; i < n; i++) {
    int u = 2+i;
    for (int j = 0; j < m; j++) {
      int v = 2+n+j;
      sum_cost += r[v][u] * c[u][v];
      sum_sell += r[v][u];
      // if (r[v][u]) printf("%d %d\n", r[v][u], c[u][v]);
    }
  }
  printf("%d\n%d", sum_sell, sum_cost);
}
