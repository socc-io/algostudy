#include <bits/stdc++.h>
using namespace std;

struct pnt {
  double x, y;
};

double distance(const pnt &a, const pnt &b) {
  double dx = a.x - b.x;
  double dy = a.y - b.y;
  return sqrt(dx*dx + dy*dy);
}

vector<int> bfs(const vector<vector<int>> &adj) {
  const int n = adj.size();
  vector<int> dist(n, 0x3f3f3f3f);
  queue<int> q;
  dist[0] = 0;
  q.push(0);
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v: adj[u]) {
      if (dist[v] != 0x3f3f3f3f) continue;
      dist[v] = dist[u] + 1;
      q.push(v);
    }
  }
  return dist;
}

double solve() {
  int n, r, d, x, y;
  cin >> n >> r >> d >> x >> y;

  vector<pnt> ps(++n);
  ps[0].x = x; ps[0].y = y;
  for (int i = 1; i < n; i++) cin >> ps[i].x >> ps[i].y;
  
  vector<vector<int>> adj(n);
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      double ld = distance(ps[i], ps[j]);
      if (ld > r) continue;
      adj[i].push_back(j);
      adj[j].push_back(i);
    }
  }

  vector<int> dist = bfs(adj);

  double ret = 0.0;
  for (int i = 1; i < n; i++) {
    ret += d / pow(2, dist[i] - 1.0);
  }
  return ret;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(2) << solve() << '\n';
}
