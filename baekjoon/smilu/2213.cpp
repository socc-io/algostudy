#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;

int n;
int wei[10001];
int mem[10001][2];
vector<int> adj[10001];
vector<pi> trk[10001][2];

int dp(int u, int f, int p) {
  int &ret = mem[u][f];
  if (ret != -1) return ret;
  if (f == 0) {
    ret = 0;
    for (int v: adj[u]) {
      if (v == p) continue;
      int off = dp(v, 0, u);
      int on  = dp(v, 1 ,u);
      if (off > on) {
        ret += off;
        trk[u][0].push_back({v, 0});
      } else {
        ret += on;
        trk[u][0].push_back({v, 1});
      }
    }
    return ret;
  } else {
    ret = wei[u];
    for (int v: adj[u]) {
      if (v == p) continue;
      trk[u][1].push_back({v, 0});
      ret += dp(v, 0, u);
    }
    return ret;
  }
}

void track(vector<int> &cont, int u, int f) {
  if (f) cont.push_back(u);
  for (auto e: trk[u][f]) {
    track(cont, e.first, e.second);
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> wei[i];
  for (int i = 1; i < n; i++) {
    int a, b; cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  adj[0].push_back(1);
  adj[1].push_back(0);
  memset(mem, 0xff, sizeof(mem));
  cout << dp(0, 0, -1) << '\n';
  vector<int> ans;
  track(ans, 0, 0);
  sort(ans.begin(), ans.end());
  for (int v: ans) cout << v << ' ';
}
