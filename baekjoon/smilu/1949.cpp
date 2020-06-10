#include <bits/stdc++.h>
using namespace std;

int n;
int wei[10001];
int mem[10001][2];
vector<int> adj[10001];

int dp(int u, int f, int p) {
  int &ret = mem[u][f];
  if (ret != -1) return ret;
  ret = 0;
  if (f) {
    ret += wei[u];
    for (int v: adj[u]) if (v != p) {
      ret += dp(v, 0, u);
    }
  } else {
    for (int v: adj[u]) if (v != p) {
      ret += max(dp(v, 0, u), dp(v, 1, u));
    }
  }
  return ret;
}

int main() {
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
}
