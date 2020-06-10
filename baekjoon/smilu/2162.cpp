#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

int ccw(pll a, pll b, pll c) {
  ll op = a.first*b.second + b.first*c.second + c.first*a.second;
  op -= (a.second*b.first + b.second*c.first + c.second*a.first);
  if (op > 0) return 1;
  else if (op == 0) return 0;
  else return -1;
}

int is_intersect(pair<pll, pll> x, pair<pll, pll> y) {
  pll a = x.first;
  pll b = x.second;
  pll c = y.first;
  pll d = y.second;
  int ab = ccw(a, b, c)*ccw(a, b, d);
  int cd = ccw(c, d, a)*ccw(c, d, b);
  if (ab == 0 && cd == 0) {
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);
    return c <= b && a <= d;
  }
  return ab <= 0 && cd <= 0;
}

int par[3001];
int sz[3001];

int root(int x) {
  return par[x] == x ? x : (par[x] = root(par[x]));
}

void merge(int a, int b) {
  a = root(a); b = root(b);
  if (a == b) return;
  par[b] = a;
  sz[a] += sz[b];
}

int main() {
  int n; cin >> n;
  vector<pair<pll,pll>> lines(n);
  for (auto &line: lines) {
    cin >> line.first.first >> line.first.second;
    cin >> line.second.first >> line.second.second;
  }
  for (int i = 0; i < n; i++) {
    par[i] = i;
    sz[i] = 1;
  }
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      if (is_intersect(lines[i], lines[j])) {
        merge(i, j);
      }
    }
  }
  int cnt = 0;
  int max_sz = 0;
  for (int i = 0; i < n; i++) {
    if (par[i] != i) continue;
    ++cnt;
    max_sz = max(max_sz, sz[i]);
  }
  cout << cnt << '\n' << max_sz << '\n';
}
