#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pi;

const int MAX_N = 100010;
const int MAX_H = 19;

int n;
ll e[MAX_N];
vector<pi> adj[MAX_N];
int par[MAX_N][MAX_H];
ll par_dis[MAX_N][MAX_H];

void init_tree(int u, int p) {
  for (int i = 1; i < MAX_H; i++) {
    int m = par[u][i-1];
    par[u][i] = par[m][i-1];
    par_dis[u][i] = par_dis[u][i-1] + par_dis[m][i-1];
  }
  for (auto e: adj[u]) {
    int v = e.first, w = e.second;
    if (v == p) continue;
    par_dis[v][0] = w;
    par[v][0] = u;
    init_tree(v, u);
  }
}

int escalate(int u, ll e) {
  for (int i = MAX_H-1; i >= 0; i--) {
    if (par_dis[u][i] <= e) {
      e -= par_dis[u][i];
      u = par[u][i];
    }
  }
  return max(1, u);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> e[i];
  for (int i = 1; i < n; i++) {
    int a, b, w; cin >> a >> b >> w;
    adj[a].emplace_back(b, w);
    adj[b].emplace_back(a, w);
  }
  init_tree(1, 0);
  for (int i = 1; i <= n; i++) {
    cout << escalate(i, e[i]) << '\n';
  }
}
