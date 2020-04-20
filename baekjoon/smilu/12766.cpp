/**
 * Divide and Conquer, Dijkstra
 * http://noj.am/12766
 */

#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long lld;
typedef pair<int,int> pii;

#define INF 0x3f3f3f3f
#define MAX_N 5001

struct edge {
  int v, l;
};

int n, b, s, r;
vector<edge> adj[MAX_N];
vector<edge> r_adj[MAX_N];

vector<int> get_distances(int cent, const vector<edge> *es) {
  priority_queue<pii> q;
  vector<bool> vs(n+1, false);
  vector<int> ds(n+1, INF);

  q.push({0, cent});
  ds[cent] = 0;

  while(!q.empty()) {
    auto up = q.top(); q.pop();
    int ud = -up.first, u = up.second;
    if (vs[u]) continue;
    vs[u] = true;
    for (edge e: es[u]) {
      int v = e.v, l = e.l;
      int vl = ud + l;
      if (vl < ds[v]) {
        ds[v] = vl;
        q.push({-vl, v});
      }
    }
  }

  return ds;
}

lld cs[5000];
lld css[5000];
lld dp[2][5000];

lld C(int i, int j) {
  lld s = i > 0 ? (css[j] - css[i-1]) : css[j];
  lld k = j-i;
  return s*k;
}

void dnc(int s, int l, int r, int pl, int pr) {
  if (l > r) return;
  int mid = (l + r) >> 1;
  int ps = s & 1, ns = 1 - ps;
  dp[ns][mid] = -1;
  int mp = -1;

  int ke = min(mid-1, pr) + 1;
  for (int k = pl; k < ke; k++) {
    lld tmp = dp[ps][k] + C(k+1, mid);
    if (dp[ns][mid] == -1 || dp[ns][mid] > tmp) {
      dp[ns][mid] = tmp;
      mp = k;
    }
  }

  dnc(s, l, mid-1, pl, mp);
  dnc(s, mid+1, r, mp, pr);
}

void calc_costs() {
  vector<int> fd = get_distances(b+1, adj);
  vector<int> rd = get_distances(b+1, r_adj);
  for (int i = 1; i <= b; i++) {
    cs[i-1] = fd[i] + rd[i];
  }
  sort(cs, cs+b);

  css[0] = cs[0];
  for (int i = 1; i < b; i++) {
    css[i] = css[i-1] + cs[i];
  }
}

int main(void)
{
  scanf("%d%d%d%d", &n, &b, &s, &r);
  while (r--) {
    int u, v, l;
    scanf("%d%d%d", &u, &v, &l);
    adj[u].push_back({v, l});
    r_adj[v].push_back({u, l});
  }
  calc_costs();

  // printf("costs: "); for (int i = 0; i < b; i++) printf("%lld ", cs[i]); puts("");

  for (int i = 0; i < b; i++) {
    dp[0][i] = css[i] * i;
  }
  for (int i = 2; i <= s; i++) {
    dnc(i, i-1, b-1, 0, b-1);
  }

  printf("%lld\n", dp[1-(s&1)][b-1]);
}
