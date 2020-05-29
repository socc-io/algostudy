#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pi;

const int MAX_N = 10010;

int n, m;
int s, e;
vector<pi> adj[MAX_N];
vector<pi> bdj[MAX_N];
int in[MAX_N];
int dst[MAX_N];
bool vis[MAX_N];
int rc;

void propagate(int u) {
  for (auto e: adj[u]) {
    int v = e.first, w = e.second;
    if (dst[v] == 0x3f3f3f3f) dst[v] = 0;
    dst[v] = max(dst[v], dst[u] + w);
    --in[v];
    if (in[v] == 0) propagate(v);
  }
}

void count(int u) {
  vis[u] = 1;
  for (auto e: bdj[u]) {
    int v = e.first, w = e.second;
    if (dst[v] != dst[u] - w) continue;
    ++rc;
    if (vis[v]) continue;
    count(v);
  }
}

int main() {
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int a, b, w; cin >> a >> b >> w;
    adj[a].emplace_back(b, w);
    bdj[b].emplace_back(a, w);
    in[b]++;
  }
  cin >> s >> e;

  memset(dst, 0x3f, sizeof(dst));
  dst[s] = 0;
  propagate(s);
  count(e);

  cout << dst[e] << '\n';
  cout << rc << '\n';
}
