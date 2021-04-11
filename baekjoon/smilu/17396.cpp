#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pi;
typedef vector<pi> vpi;
typedef priority_queue<pi, vpi, greater<pi>> pq;

int n, m;
bool vis[100100];
bool vs[100100];
vector<pi> adj[100100];

ll dijkstra() {
  pq q;
  q.push(make_pair(0, 0));
  while (!q.empty()) {
    ll u = q.top().second, ut = q.top().first;
    q.pop();
    if (vs[u]) continue;
    vs[u] = true;
    if (u == n-1) return ut;
    for (auto e: adj[u]) {
      ll v = e.first, vt = ut + e.second;
      if (vs[v]) continue;
      q.push(make_pair(vt, v));
    }
  }
  return -1;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> vis[i];
  vis[n-1] = 0;
  for (int i = 0; i < m; i++) {
    int a, b, t;
    cin >> a >> b >> t;
    if (vis[a] || vis[b]) continue;
    adj[a].push_back(make_pair(b, t));
    adj[b].push_back(make_pair(a, t));
  }
  cout << dijkstra();
}
