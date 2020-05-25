#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1000001;

int n;
vector<int> adj[MAX_N];
int par[MAX_N];

int mem[MAX_N][2];
int dp(int u, int c) {
  int &ret = mem[u][c];
  if (ret != -1) return ret;
  ret = c;
  if (c) {
    for (int v: adj[u]) {
      if (v == par[u]) continue;
      ret += min(dp(v, 0), dp(v, 1));
    }
  } else {
    for (int v: adj[u]) {
      if (v == par[u]) continue;
      ret += dp(v, 1);
    }
  }
  return ret;
}

void init_tree(int u, int p) {
  par[u] = p;
  for (int v: adj[u]) {
    if (v == p) continue;
    init_tree(v, u);
  }
}

int main(void) {
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    int a, b; scanf("%d%d", &a, &b);
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  init_tree(1, 0);
  memset(mem, 0xff, sizeof(mem));
  printf("%d\n", min(dp(1, 0), dp(1, 1)));
}
