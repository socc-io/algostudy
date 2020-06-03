#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pl;
typedef pair<int, int> pi;

ll extended_gcd(ll a, ll b, ll *x, ll *y) {
  if (a == 0) {
    *x = 0;
    *y = 1;
    return b;
  }
  ll x1, y1;
  ll gcd = extended_gcd(b % a, a, &x1, &y1);
  *x = y1 - (b/a) * x1;
  *y = x1;
  return gcd;
}

ll n, m;
ll x[101], y[101];
vector<int> adj[101];
int dist[101];
int bk[101];

bool check_conn(int p, int q) {
  if (y[p] > y[q]) swap(p, q);
  ll a, b;
  ll g = extended_gcd(y[p], y[q], &a, &b);
  ll t = (n-x[q])/y[q]*y[q] + x[q] - x[p];
  if (t < 0) return false;
  if (t % g) return false;
  a *= t/g; b *= t/g;

  ll k = y[q]/g;
  k = (k-a-1)/k;
  a += k * y[q]/g;
  b -= k * y[p]/g;

  return b >= 0;
}

bool check_including(ll x, ll y, ll v) {
  ll c = v - x;
  if (c < 0) return false;
  return (c % y) == 0;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n >> m;
  for (int i = 0; i < m; i++) cin >> x[i] >> y[i];
  for (int i = 0; i < m; i++) {
    for (int j = i+1; j < m; j++) {
      if (check_conn(i, j)) {
        adj[i].push_back(j);
        adj[j].push_back(i);
        // cout << "conn: " << i+1 << ' ' << j+1 << '\n';
      }
    }
  }
  ll s, e; cin >> s >> e;
  priority_queue<pi, vector<pi>, greater<pi>> pq;
  vector<bool> vis(m);
  for (int i = 0; i < m; i++) {
    dist[i] = check_including(x[i], y[i], e) ? 0 : 0x3f3f3f3f;
    bk[i] = i;
    if (!dist[i]) {
      pq.push({0, i});
      // cout << "start " << i << '\n';
    }
  }
  while (!pq.empty()) {
    auto t = pq.top(); pq.pop();
    int ud = t.first, u = t.second;
    if (vis[u]) continue;
    vis[u] = true;
    for (int v: adj[u]) {
      int vd = ud + 1;
      if (vd < dist[v]) {
        dist[v] = vd;
        bk[v] = u;
        pq.push({vd, v});
      }
    }
  }
  int min_dist = 0x3f3f3f3f;
  int min_idx = -1;
  for (int i = 0; i < m; i++) {
    if (check_including(x[i], y[i], s)) {
      if (dist[i] < min_dist) {
        min_dist = dist[i];
        min_idx = i;
      }
      // cout << "end " << i << '\n';
    }
  }
  if (min_dist == 0x3f3f3f3f) {
    cout << "-1\n";
    return 0;
  }
  cout << min_dist+1 << '\n';
  int cur = min_idx;
  while (bk[cur] != cur) {
    cout << cur+1 << '\n';
    cur = bk[cur];
  }
  cout << cur+1 << '\n';
}
