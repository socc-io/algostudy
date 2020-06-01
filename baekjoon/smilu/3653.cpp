#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 200020;

struct BIT {
  int ft[MAX_N];
  void update(int x, int v) {
    for (int i = x; i <= MAX_N; i+=(i&-i)) ft[i] += v;
  }
  int query(int x) {
    int ret = 0;
    for (int i = x; i > 0; i-=(i&-i)) ret += ft[i];
    return ret;
  }
  int query(int a, int b) {
    return query(b) - query(a-1);
  }
} bit;

int pos[MAX_N];

void solve() {
  memset(&bit, 0x00, sizeof(BIT));
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    bit.update(i, 1);
    pos[i] = n-i+1;
  }
  for (int i = 1; i <= m; i++) {
    int v; cin >> v;
    cout << bit.query(pos[v]+1, MAX_N-1) << ' ';
    bit.update(pos[v], -1);
    pos[v] = n+i;
    bit.update(pos[v], 1);
  } cout << '\n';
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t;
  while (t--) solve();
}
