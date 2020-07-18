#include <bits/stdc++.h>
using namespace std;

int fs[10];
void init_fs() {
  fs[0] = fs[1] = 1;
  for (int i = 2; i <= 9; i++) fs[i] = fs[i-1] * i;
}

int perm(int a, int b) {
  return fs[a]/fs[a-b];
}
int comb(int a, int b) {
  if (a < b) return 0;
  return perm(a, b)/fs[b];
}

double solve() {
  int ret = 0;
  int n, m, k; cin >> n >> m >> k;
  for (int i = k; i <= m; i++) {
    ret += comb(m, i) * comb(n-m, m-i);
  }
  return ((double)ret) / comb(n, m);
}

int main() {
  init_fs();
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(16) << solve();
}
