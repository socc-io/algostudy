#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pi;
typedef pair<ll, pair<ll, ll>> pii;

ll dist[1010][1010];
bool vis[1010][1010];

ll n, m, k;
ll src, dst;
vector<pi> adj[1010];

void calc_dist() {
  memset(dist, 0x3f, sizeof(dist));
  memset(vis, 0x00, sizeof(vis));
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  dist[src][0] = 0;
  pq.push({0, {src, 0}});
  while (!pq.empty()) {
    auto t = pq.top(); pq.pop();
    auto u = t.second;
    ll ud = t.first;
    if (vis[u.first][u.second]) continue;
    vis[u.first][u.second] = true;
    if (u.second >= n+1) continue;
    for (auto e: adj[u.first]) {
      pi v = {e.first, u.second + 1};
      ll vd = ud + e.second;
      if (vd < dist[v.first][v.second]) {
        dist[v.first][v.second] = vd;
        pq.push({vd, v});
      }
    }
  }
}

ll min_dist(ll v) {
  ll ans = dist[dst][0];
  for (ll i = 1; i <= n; i++) {
    ans = min(ans, dist[dst][i] + v * i);
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n >> m >> k;
  cin >> src >> dst;
  for (ll i = 0; i < m; i++) {
    ll a, b, w; cin >> a >> b >> w;
    adj[a].push_back({b, w});
    adj[b].push_back({a, w});
  }
  calc_dist();
  cout << min_dist(0) << '\n';
  ll v = 0;
  for (ll i = 0; i < k; i++) {
    ll sv; cin >> sv; v += sv;
    cout << min_dist(v) << '\n';
  }
}
