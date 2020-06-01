#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,ll> pi;

const int MAX_N = 100010;

int n, m;
pi par[MAX_N];

pi get_par(int u) {
  if (par[u].first == u) return par[u];
  auto t = get_par(par[u].first);
  return par[u] = make_pair(t.first, t.second + par[u].second);
}

void solve() {
  for (int i = 0; i <= n; i++) par[i] = make_pair(i, 0ll);
  while (m--) {
    char ch; cin >> ch;
    if (ch == '!') {
      int a, b, c; cin >> a >> b >> c;
      auto A = get_par(a), B = get_par(b);
      if (A.first != B.first) {
        par[A.first] = make_pair(B.first, c - A.second + B.second);
      }
    } else {
      int a, b; cin >> a >> b;
      auto A = get_par(a), B = get_par(b);
      if (A.first != B.first) cout << "UNKNOWN" << '\n';
      else {
        cout << A.second - B.second << '\n';
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  while (1) {
    cin >> n >> m;
    if (n == 0 && m == 0) return 0;
    solve();
  }
}
