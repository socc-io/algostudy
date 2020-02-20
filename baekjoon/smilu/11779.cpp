#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define INF 0x7FFFFFF0

typedef pair<int,int> pii;

int n;
int src, dst;
vector<pii> es[1000];

int main(void)
{
  int m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++) {
    int f, t, c;
    scanf("%d%d%d", &f, &t, &c);
    --f; --t;
    es[f].push_back(make_pair(t, c));
  }
  scanf("%d%d", &src, &dst); --src; --dst;

  priority_queue<pii, vector<pii>, greater<pii>> q;
  q.push(make_pair(0, src));
  vector<int>  ds(n, INF); ds[src] = 0;
  vector<bool> vs(n, false);
  vector<int>  bt(n, -1);
  while(!q.empty()) {
    int ud = q.top().first;
    int u  = q.top().second;
    q.pop();
    if (vs[u]) continue;
    vs[u] = true;
    for (int i = 0; i < es[u].size(); i++) {
      int v  = es[u][i].first;
      int ec = es[u][i].second;
      int nd = ud + ec;
      if (nd < ds[v]) {
        ds[v] = nd;
        q.push(make_pair(nd, v));
        bt[v] = u;
        // printf("ds[%d]: %d, bt[%d]: %d\n", v+1, nd, v+1, u+1);
      }
    }
  }

  vector<int> ts; ts.push_back(dst);
  int cur = dst;
  while(cur != src) {
    ts.push_back(bt[cur]);
    cur = bt[cur];
  }
  reverse(ts.begin(), ts.end());

  printf("%d\n%lu\n", ds[dst], ts.size());
  for (int i = 0; i < ts.size(); i++) {
    printf("%d ", ts[i] + 1);
  }
}
