#include <bits/stdc++.h>
using namespace std;

int n;
int w[30];
set<int> ps;

void apply_weight(const set<int> & src, set<int> & dst, int w) {
  dst.insert(w);
  dst.insert(-w);
  for (const int pv: src) {
    dst.insert(pv);
    dst.insert(pv + w);
    dst.insert(pv - w);
  }
}

void prep() {
  set<int> s[2];
  int t = 0;
  for (int i = 0; i < n; i++) {
    s[1-t].clear();
    apply_weight(s[t], s[1-t], w[i]);
    t = 1 - t;
  }
  ps = s[t];
}

bool solve(int q) {
  return ps.find(q) != ps.end();
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n;
  for (int i = 0; i < n; i++) cin >> w[i];
  prep();
  int t; cin >> t;
  while (t--) {
    int q; cin >> q;
    cout << (solve(q) ? 'Y' : 'N') << ' ';
  }
}
