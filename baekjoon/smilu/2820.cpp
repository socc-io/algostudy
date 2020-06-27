#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX_N = 500050;

struct BIT {
  ll ft[MAX_N];
  void update(int x, ll v) {
    for (int i = x; i <= MAX_N; i+=(i&-i)) ft[i] += v;
  }
  void update(int a, int b, ll v) {
    update(a, v);
    update(b+1, -v);
  }
  ll query(int x) {
    ll ret = 0;
    for (int i = x; i > 0; i-=(i&-i)) ret += ft[i];
    return ret;
  }
} bit;

int n, m;
int init_pay[MAX_N];
int par[MAX_N];
int n_in[MAX_N], piv_dfsn;
int n_out[MAX_N];
vector<int> adj[MAX_N];

void init_tree(int u) {
  n_in[u] = ++piv_dfsn;
  for (int v: adj[u]) init_tree(v);
  n_out[u] = piv_dfsn;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n >> m;
  cin >> init_pay[1];
  for (int i = 2; i <= n; i++) {
    cin >> init_pay[i] >> par[i];
    adj[par[i]].push_back(i);
  }
  init_tree(1);
  for (int i = 1; i <= n; i++) {
    // cout << "update " << n_in[i] << " + " << init_pay[i] << '\n';
    bit.update(n_in[i], n_in[i], init_pay[i]);
  }
  while (m--) {
    char cmd; cin >> cmd;
    if (cmd == 'p') {
      int a, x; cin >> a >> x;
      // cout << "update " << n_in[a]+1 << " ~ " << n_out[a] << " + " << x << '\n';
      bit.update(n_in[a]+1, n_out[a], x);
    } else {
      int u; cin >> u;
      // cout << n_in[u] << ": ";
      cout << bit.query(n_in[u]) << '\n';
    }
  }
}
