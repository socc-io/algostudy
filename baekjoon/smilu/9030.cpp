#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct rect {
  ll x, y, w, h;
};

ll diff_2(ll a, ll b) {
  ll diff = a - b;
  return diff * diff;
}

bool collide(pair<ll, ll> a, pair<ll, ll> b) {
  return a.first <= b.second && a.second >= b.first;
}

ll distance_2(pair<ll, ll> a, pair<ll, ll> b) {
  ll dx = a.first  - b.first;
  ll dy = a.second - b.second;
  return dx*dx + dy*dy;
}

ll distance_2(const rect &a, const rect &b) {
  ll ret = LLONG_MAX;
  if (collide({a.x, a.x + a.w}, {b.x, b.x + b.w})) {
    ret = min(ret, diff_2(a.y      , b.y      ));
    ret = min(ret, diff_2(a.y + a.h, b.y      ));
    ret = min(ret, diff_2(a.y      , b.y + b.h));
    ret = min(ret, diff_2(a.y + a.h, b.y + b.h));
  }
  if (collide({a.y, a.y + a.h}, {b.y, b.y + b.h})) {
    ret = min(ret, diff_2(a.x      , b.x      ));
    ret = min(ret, diff_2(a.x + a.w, b.x      ));
    ret = min(ret, diff_2(a.x      , b.x + b.w));
    ret = min(ret, diff_2(a.x + a.w, b.x + b.w));
  }
  vector<pair<ll, ll>> a_corners = {
    {a.x      , a.y      },
    {a.x + a.w, a.y      },
    {a.x      , a.y + a.h},
    {a.x + a.w, a.y + a.h},
  };
  vector<pair<ll, ll>> b_corners = {
    {b.x      , b.y      },
    {b.x + b.w, b.y      },
    {b.x      , b.y + b.h},
    {b.x + b.w, b.y + b.h},
  };
  for (auto ac: a_corners) for (auto bc: b_corners) {
    ret = min(ret, distance_2(ac, bc));
  }
  return ret;
}

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

ll solve() {
  int n; cin >> n;
  vector<rect> rects(n);
  for (auto &r: rects) {
    cin >> r.x >> r.y >> r.w >> r.h;
    r.h *= -1;
  }
  vector<vector<ll>> cost(n, vector<ll>(n));
  for (int i = 0; i < n; i++) for (int j = i+1; j < n; j++) {
    cost[i][j] = distance_2(rects[i], rects[j]);
    cost[j][i] = cost[i][j];
  }
  // for (int i = 0; i < n; i++) {
  //   for (int j = 0; j < n; j++) {
  //     cout << cost[i][j] << ' ';
  //   } cout << '\n';
  // }
  return prim(cost);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t;
  while (t--) cout << solve() << '\n';
}
