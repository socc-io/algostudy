#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll prim(const vector<vector<ll>> &cost) {
  ll ret = 0;
  int cnt = 0;
  int n = (int)cost.size();
  vector<bool> visit(n);
  priority_queue<
    pair<ll,int>,
    vector<pair<ll,int>>,
    greater<pair<ll,int>>
  > pq;
  pq.push({0, 0});
  while (1) {
    auto t = pq.top(); pq.pop();
    int u = t.second;
    if (visit[u]) continue;
    visit[u] = true;
    ret += t.first;
    ++cnt;
    if (cnt == n) break;
    for (int v = 0; v < n; v++) {
      if (u == v || visit[v]) continue;
      pq.push({cost[u][v], v});
    }
  }
  return ret;
}