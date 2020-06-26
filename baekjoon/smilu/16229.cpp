#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

vi get_pi(const string &s) {
  int n = s.size(), j = 0;
  vi pi(n, 0);
  for (int i = 1; i < n; i++) {
    while (j > 0 && s[i] != s[j]) j = pi[j-1];
    if (s[i] == s[j]) pi[i] = ++j;
  }
  return pi;
}

vi get_kv(const vi &pi) {
  const int n = pi.size();
  vi ret = vi(n);
  int j = n;
  while (j) {
    ret[n-j] = 1;
    j = pi[j-1];
  }
  return ret;
}

int solve() {
  int n, m; cin >> n >> m;
  string s; cin >> s;

  // if (m == 0 && (n & 1)) return 0;

  const vi pi = get_pi(s);
  const vi kv = get_kv(pi);

  // cout << "ss: "; for (char v: s) cout << v << ' '; cout << '\n';
  // cout << "pi: "; for (int v: pi) cout << v << ' '; cout << '\n';
  // cout << "kv: "; for (int v: kv) cout << v << ' '; cout << '\n';

  const int msz = min((n+m)>>1, n);
  for (int sz = msz; sz > 0; sz--) {
    bool flag = false;
    for (int i = sz; i < n; i += sz) {
      if (i + sz > n+m || kv[i] == 0) {
        flag = true;
        break;
      }
    }
    if (flag) continue;
    return sz;
  }

  return 0;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << solve() << '\n';
}
